/*
 * cart_grid.h
 *
 *  Created on: Sep 18, 2019
 *      Author: akadar
 */

#ifndef CART_GRID_H_
#define CART_GRID_H_

#include <vector>
#include <algorithm> // std::minmax_element, std::fill
#include <cassert>

#include "io.h"

#define DUMMY_VAL -7
#define DUMMY_GRID_DATA_VAL 0
#define DUMMY_BUFFER_VAL -11

template<unsigned short dim = 3, unsigned short halo_width = 1> class cart_grid{
public:
	cart_grid() = delete;

	cart_grid(const std::vector<size_t>& nodes_,
			const std::vector<int>& neighbours_,
			const std::vector<double>& offset_,
			const std::vector<double>& delta_,
			const std::vector<double>& global_origin_,
			double dt_){

		// Some useful checks
		constexpr bool check_dim = (dim>=1 && dim<=3);
		static_assert(check_dim,"Only dimension 1, 2 and 3 are supported");

		constexpr bool check_halo = (halo_width==1);
		static_assert(check_halo,"Only halo of width 1 is supported");

		assert(nodes_.size()==dim);
		assert(neighbours_.size()==2*dim);
		assert(offset_.size()==dim);
		assert(delta_.size()==dim);
		assert(global_origin_.size()==dim);

		// Initialize data members
		size_t count{1};
		for(const auto& elem:nodes_){
			in_nodes.push_back(elem);
			nodes.push_back(elem+2*halo_width);
			count*=(elem+2*halo_width);
		}

		neighbours = neighbours_;
		offset = offset_;
		delta = delta_;
		global_origin = global_origin_;
		dt = dt_;

		neighbours.resize(2*dim,DUMMY_VAL);

		// allocate grid data (including halo region)
		data.resize(count,DUMMY_GRID_DATA_VAL);
		data.shrink_to_fit();

		// allocate buffer data
		size_t buf_size{0};
		switch (dim){
		case 1:
			buf_size = 1;
			break;
		case 2:
			buf_size = (in_nodes[0] > in_nodes[1] ? in_nodes[0] : in_nodes[1]);
			break;
		case 3:
			buf_size = in_nodes[0]*in_nodes[1];
			if(buf_size < in_nodes[1]*in_nodes[2]) buf_size = in_nodes[1]*in_nodes[2];
			if(buf_size < in_nodes[2]*in_nodes[0]) buf_size = in_nodes[2]*in_nodes[0];
			break;
		default: std::cout<<"Unknown dimension \n"; std::terminate();
		}

		buf_size *= halo_width;
		inbuffer.resize(buf_size,DUMMY_BUFFER_VAL);
		inbuffer.shrink_to_fit();
		outbuffer.resize(buf_size,DUMMY_BUFFER_VAL);
		outbuffer.shrink_to_fit();
	}

	// helper functions

	void fill(const double& x){
		std::fill(data.begin(),data.end(),x);
	}

	void debug_fill(const double& x){
		double ctr{(x+1)*1000};
		for(auto& elem:data) {
			elem = ctr;
			++ctr;
		}
	}

	void fill_interior(double (*f)(double,double,double)){

		double xinit, yinit, zinit;

		switch(dim){
		case 1:
			xinit = global_origin[0] + offset[0]*delta[0];
			for(size_t i=1; i<(nodes[0]-1); ++i){
				 data[i] = f(xinit+(i-1)*delta[0],0,0);
			}
			break;
		case 2:
			xinit = global_origin[0] + offset[0]*delta[0];
			yinit = global_origin[1] + offset[1]*delta[1];
			for(size_t j=1; j<(nodes[1]-1); ++j){
				for(size_t i=1; i<(nodes[0]-1); ++i){
					data[i+nodes[0]*j] = f(xinit+(i-1)*delta[0],yinit+(j-1)*delta[1],0);
				}
			}
			break;
		case 3:
			xinit = global_origin[0] + offset[0]*delta[0];
			yinit = global_origin[1] + offset[1]*delta[1];
			zinit = global_origin[2] + offset[2]*delta[2];
			for(size_t k=1; k<(nodes[2]-1); ++k){
				for(size_t j=1; j<(nodes[1]-1); ++j){
					for(size_t i=1; i<(nodes[0]-1); ++i){
						data[i+nodes[0]*j+nodes[0]*nodes[1]*k] =
								f(xinit+(i-1)*delta[0],yinit+(j-1)*delta[1],zinit+(k-1)*delta[2]);
					}
				}
			}
			break;
		}
	}

	int get_neighbour_rank(int dir, std::string left_right) const{

		assert(assert_dir(dir));

		int add;
		if(left_right.compare("left")!=0 && left_right.compare("right")!=0){
			std::cout<<"Wrong neighbor information queried\n";
			std::terminate();
		}

		if(left_right.compare("left")==0)
			add = 0;

		if(left_right.compare("right")==0)
			add = 1;

		return neighbours[2*dir+add];
	}

	int get_bsize(int dir) const{

		assert(assert_dir(dir));

		size_t bsize;

		switch(dim){
		case 1:
			bsize = 1;
			break;
		case 2:
			bsize = (dir==0 ? in_nodes[1] : in_nodes[0]);
			break;
		case 3:
			bsize = (dir==0 ? (in_nodes[1]*in_nodes[2]) :
					(dir==1 ? (in_nodes[2]*in_nodes[0]) : (in_nodes[0]*in_nodes[1])));
			break;
		default: std::cout<<"Unknown dimension \n"; std::terminate();
		}

		return halo_width*bsize;
	}

	double* get_inbuffer() {
		return inbuffer.data();
	}

	double* get_outbuffer(){
		return outbuffer.data();
	}

	void copy_sendrecv_buf(int dir, std::string Op, std::string dir_shift){

		assert(assert_dir(dir));

		if(dir_shift.compare("pos")!=0 && dir_shift.compare("neg")!=0){
			std::cout<<"dir_shift should be either pos or neg\n";
			std::terminate();
		}

		if(Op.compare("send")!=0 && Op.compare("receive")!=0){
			std::cout<<"Op should be either send or receive\n";
			std::terminate();
		}

		size_t i{0},j{0},k{0}, index;
		size_t ctr{0};

		if(Op.compare("send")==0){
			if(dir_shift.compare("pos")==0)
				index = nodes[dir]-2;
			else
				index = 0+1;
		} else
		if(Op.compare("receive")==0){
			if(dir_shift.compare("pos")==0)
				index = 0;
			else
				index = nodes[dir]-1;
		}

		if(dir==0){ // fixed X
			i = index;
		} else

		if(dir==1){ // fixed Y
			j = index;
		} else

		if(dir==2){ // fixed Z
			k = index;
		}

		switch(dim){

		case 1:

			if(Op.compare("send")==0){
				if(dir_shift.compare("pos")==0)
					outbuffer[0] = data[nodes[0]-2];
				else
					outbuffer[0] = data[0+1];
			}
			if(Op.compare("receive")==0){
				if(dir_shift.compare("pos")==0)
					data[0] = inbuffer[0];
				else
					data[nodes[0]-1] = inbuffer[0];
			}

			break;

		case 2:

			if(dir==0){ // fixed X

				for(j=1; j<(nodes[1]-1); ++j){
					if(Op.compare("send")==0){
						outbuffer[ctr] = data[i+nodes[0]*j];
					}
					if(Op.compare("receive")==0){
						data[i+nodes[0]*j]= inbuffer[ctr];
					}
					++ctr;
					}

			} else

			if(dir==1){ // fixed Y

				for(i=1; i<(nodes[0]-1); ++i){
					if(Op.compare("send")==0){
						outbuffer[ctr] = data[i+nodes[0]*j];
					}
					if(Op.compare("receive")==0){
						data[i+nodes[0]*j]= inbuffer[ctr];
					}
					++ctr;
					}

			} else

			{
				std::cout<<"Unexpected direction\n";
				std::terminate();
			}

			break;

		case 3:

			if(dir==0){ // fixed X

				for(k=1; k<(nodes[2]-1); ++k){
					for(j=1; j<(nodes[1]-1); ++j){
						if(Op.compare("send")==0)
							outbuffer[ctr] = data[i+nodes[0]*j+nodes[0]*nodes[1]*k];
						if(Op.compare("receive")==0){
							data[i+nodes[0]*j+nodes[0]*nodes[1]*k] = inbuffer[ctr];
						}
						++ctr;
						}
					}

			} else

			if(dir==1){ // fixed Y

				for(k=1; k<(nodes[2]-1); ++k){
					for(i=1; i<(nodes[0]-1); ++i){
						if(Op.compare("send")==0)
							outbuffer[ctr] = data[i+nodes[0]*j+nodes[0]*nodes[1]*k];
						if(Op.compare("receive")==0){
							data[i+nodes[0]*j+nodes[0]*nodes[1]*k] = inbuffer[ctr];
						}
						++ctr;
						}
					}

			} else

			if(dir==2){ // fixed Z

				for(j=1; j<(nodes[1]-1); ++j){
					for(i=1; i<(nodes[0]-1); ++i){
						if(Op.compare("send")==0)
							outbuffer[ctr] = data[i+nodes[0]*j+nodes[0]*nodes[1]*k];
						if(Op.compare("receive")==0){
							data[i+nodes[0]*j+nodes[0]*nodes[1]*k] = inbuffer[ctr];
						}
						++ctr;
						}
					}

			} else

			{
				std::cout<<"Unexpected direction\n";
				std::terminate();
			}

			break;

		default: std::cout<<"Unknown dimension \n"; std::terminate();

		}

	}

	void exec_jacobi_kernel(){

		std::vector<double> temp(data);

		switch(dim){
		case 1:
			for(size_t i=1; i<(nodes[0]-1); ++i){
				 double dphidt = (temp[i+1]
							     +temp[i-1]
							   -2*temp[i+0])/(delta[0]*delta[0]);

				 data[i] = dt*dphidt+temp[i];
			}
			break;
		case 2:
			for(size_t j=1; j<(nodes[1]-1); ++j){
				for(size_t i=1; i<(nodes[0]-1); ++i){

					// (i)+nodes[0]*(j)

					double x_dphidt = (temp[(i+1)+nodes[0]*(j)]
							          +temp[(i-1)+nodes[0]*(j)]
								    -2*temp[(i+0)+nodes[0]*(j)])/(delta[0]*delta[0]);
					double y_dphidt = (temp[(i)+nodes[0]*(j+1)]
							          +temp[(i)+nodes[0]*(j-1)]
								    -2*temp[(i)+nodes[0]*(j+0)])/(delta[1]*delta[1]);

					double dphidt = x_dphidt + y_dphidt;

					data[i+nodes[0]*j] = dt*dphidt+temp[i+nodes[0]*j];
				}
			}
			break;
		case 3:
			for(size_t k=1; k<(nodes[2]-1); ++k){
				for(size_t j=1; j<(nodes[1]-1); ++j){
					for(size_t i=1; i<(nodes[0]-1); ++i){

						// (i)+nodes[0]*(j)+nodes[0]*nodes[1]*(k)

						double x_dphidt = (temp[(i+1)+nodes[0]*(j)+nodes[0]*nodes[1]*(k)]
								          +temp[(i-1)+nodes[0]*(j)+nodes[0]*nodes[1]*(k)]
									    -2*temp[(i+0)+nodes[0]*(j)+nodes[0]*nodes[1]*(k)])/(delta[0]*delta[0]);

						double y_dphidt = (temp[(i)+nodes[0]*(j+1)+nodes[0]*nodes[1]*(k)]
								          +temp[(i)+nodes[0]*(j-1)+nodes[0]*nodes[1]*(k)]
									    -2*temp[(i)+nodes[0]*(j+0)+nodes[0]*nodes[1]*(k)])/(delta[1]*delta[1]);

						double z_dphidt = (temp[(i)+nodes[0]*(j)+nodes[0]*nodes[1]*(k+1)]
								          +temp[(i)+nodes[0]*(j)+nodes[0]*nodes[1]*(k-1)]
									    -2*temp[(i)+nodes[0]*(j)+nodes[0]*nodes[1]*(k+0)])/(delta[2]*delta[2]);

						double dphidt = x_dphidt + y_dphidt + z_dphidt;

						data[i+nodes[0]*j+nodes[0]*nodes[1]*k] =
								dt*dphidt+temp[i+nodes[0]*j+nodes[0]*nodes[1]*k];
					}
				}
			}
			break;
		}

	}

	void print_info() const{

		print_vec("Nodes including halo: ",nodes);
		print_vec("Offset: ",offset);

		printf("Buffer size = %zd\n", inbuffer.size());

		auto minmax = std::minmax_element(inbuffer.begin(), inbuffer.end());
		std::cout << "inbuffer min = " << *minmax.first << ", max = " << *minmax.second << '\n';
		minmax = std::minmax_element(outbuffer.begin(), outbuffer.end());
		std::cout << "outbuffer min = " << *minmax.first << ", max = " << *minmax.second << '\n';

		std::cout<<"neighbours: ";
		for(const auto& elem : neighbours) std::cout<<elem<<" ";

		std::cout<<"\n";
	}

	void print_grid_data() const{

		std::cout<<"\n";

		std::cout<<"Grid data:\n";

		switch(dim){
		case 1:
			for(size_t i=0; i<nodes[0]; ++i){
				 std::cout<<data[i]<<" ";
			}
			break;
		case 2:
			for(int j=nodes[1]-1; j>=0; --j){
				std::cout<<"\n";
				for(size_t i=0; i<nodes[0]; ++i){
					std::cout<<data[i+nodes[0]*j]<<" ";
				}
			}
			break;
		case 3:
			for(size_t k=0; k<nodes[2]; ++k){
				std::cout<<"\nk = "<<k;
				for(int j=nodes[1]-1; j>=0; --j){
					std::cout<<"\n";
					for(size_t i=0; i<nodes[0]; ++i){
						std::cout<<data[i+nodes[0]*j+nodes[0]*nodes[1]*k]<<" ";
					}
				}
			}
			break;
		}
		std::cout<<"\n";
	}

	bool assert_dir(int dir) const{

		bool flag{true};

		switch(dim){
		case 1: if(dir!=0) flag = false; break;
		case 2: if(dir!=0 && dir!=1) flag = false; break;
		case 3: if(dir!=0 && dir!=1 && dir!=2) flag = false; break;
		default: std::cout<<"Unknown dimension \n"; std::terminate();
		}

		return flag;
	}

private:

	double dt;
	std::vector<double> global_origin;
	std::vector<double> delta;
	std::vector<double> offset;

	std::vector<size_t> in_nodes;
	std::vector<size_t> nodes;
	std::vector<int> neighbours;

	std::vector<double> data;
	std::vector<double> inbuffer;
	std::vector<double> outbuffer;
};

#endif /* CART_GRID_H_ */
