/*
 * cart_grid.h
 *
 *  Created on: Sep 18, 2019
 *      Author: akadar
 */

#ifndef CART_GRID_H_
#define CART_GRID_H_

#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric> // std::accumulate
#include <functional> // std::multiplies
#include "io.h"

#define DUMMY_BUFFER_VAL -7

template<unsigned short dim = 3> class cart_grid{
public:
	cart_grid() = delete;

	cart_grid(const std::vector<size_t>& nodes_){

		size_t count{1};

		for(const auto& elem : nodes_){
			in_nodes.push_back(elem);
			nodes.push_back(elem+2);
			count*=(elem+2);
		}

		neighbours.resize(2*dim,0);

		// allocate interior grid data
		data.resize(count,0);
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
		inbuffer.resize(buf_size,DUMMY_BUFFER_VAL);
		inbuffer.shrink_to_fit();
		outbuffer.resize(buf_size,DUMMY_BUFFER_VAL);
		outbuffer.shrink_to_fit();
	}

	// helper functions

	void fill(const double& x){
		std::fill(data.begin(),data.end(),x);
	}

	void set_neighbours(const std::vector<int>& x){
		neighbours = x;
	}

	int get_neighbour_rank(int dir, std::string left_right) const{
		int add;
		if(left_right.compare("left")!=0 && left_right.compare("right")!=0){
			std::cout<<"Wrong neighbor information queried\n";
			std::terminate();
		}
		if(left_right.compare("left")==0)
			add = 0;
		if(left_right.compare("right")==0)
			add = 1;
		return neighbours[dir*2+add];
	}

	int get_bsize(int dir) const{
		size_t bsize;
		switch(dim){
		case 1:
			if(dir!=0) {std::cout<<"Unexpected direction\n"; std::terminate();}
			bsize = 1;
			break;
		case 2:
			if(dir!=0 && dir!=1) {std::cout<<"Unexpected direction\n"; std::terminate();}
			bsize = (dir==0 ? in_nodes[1] : in_nodes[0]);
			break;
		case 3:
			if(dir!=0 && dir!=1 && dir!=2) {std::cout<<"Unexpected direction\n"; std::terminate();}
			bsize = (dir==0 ? in_nodes[1]*in_nodes[2] :
					(dir==1 ? in_nodes[2]*in_nodes[0] : in_nodes[0]*in_nodes[1]));
		}
		return bsize;
	}

	double* get_inbuffer(){
		return inbuffer.data();
	}

	double* get_outbuffer(){
		return outbuffer.data();
	}

	void copy_sendrecv_buf(int dir, std::string Op, std::string dir_shift){

		if(dir_shift.compare("pos")!=0 && dir_shift.compare("neg")!=0){
			std::cout<<"dir_shift should be either pos or neg\n";
			std::terminate();
		}

		if(Op.compare("send")!=0 && Op.compare("receive")!=0){
			std::cout<<"Op should be either send or receive\n";
			std::terminate();
		}

		size_t i,j,k;
		size_t ctr{0};

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

				if(Op.compare("send")==0){
					if(dir_shift.compare("pos")==0)
						i = nodes[dir]-2;
					else
						i = 0+1;
				}

				if(Op.compare("receive")==0){
					if(dir_shift.compare("pos")==0)
						i = 0;
					else
						i = nodes[dir]-1;
				}

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

				if(Op.compare("send")==0){
					if(dir_shift.compare("pos")==0)
						j = nodes[dir]-2;
					else
						j = 0+1;
				}

				if(Op.compare("receive")==0){
					if(dir_shift.compare("pos")==0)
						j = 0;
					else
						j = nodes[dir]-1;
				}

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
				if(Op.compare("send")==0){
					if(dir_shift.compare("pos")==0)
						i = nodes[dir]-2;
					else
						i = 0+1;
				}

				if(Op.compare("receive")==0){
					if(dir_shift.compare("pos")==0)
						i = 0;
					else
						i = nodes[dir]-1;
				}

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
				if(Op.compare("send")==0){
					if(dir_shift.compare("pos")==0)
						j = nodes[dir]-2;
					else
						j = 0+1;
				}

				if(Op.compare("receive")==0){
					if(dir_shift.compare("pos")==0)
						j = 0;
					else
						j = nodes[dir]-1;
				}

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

				if(Op.compare("send")==0){
					if(dir_shift.compare("pos")==0)
						k = nodes[dir]-2;
					else
						k = 0+1;
				}

				if(Op.compare("receive")==0){
					if(dir_shift.compare("pos")==0)
						k = 0;
					else
						k = nodes[dir]-1;
				}

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

		default: std::cout<<"Unknown direction \n"; std::terminate();

		}

	}

	void print_info() const{
		print_vec("Nodes including halo: ",nodes);
		printf("buffer size = %zd\n", inbuffer.size());
		auto minmax = std::minmax_element(inbuffer.begin(), inbuffer.end());
		std::cout << "inbuffer min = " << *minmax.first << ", max = " << *minmax.second << '\n';
		minmax = std::minmax_element(outbuffer.begin(), outbuffer.end());
		std::cout << "outbuffer min = " << *minmax.first << ", max = " << *minmax.second << '\n';
     	std::cout<<"neighbours : ";
		for(const auto& elem : neighbours) std::cout<<elem<<" ";
		std::cout<<"\n";
	}

	void print_grid_data() const{

		std::cout<<"\n";

		std::cout<<"Grid data:";

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
				std::cout<<"\n";
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

private:

	std::vector<size_t> in_nodes;
	std::vector<size_t> nodes;
	std::vector<int> neighbours;

	std::vector<double> data;
	std::vector<double> inbuffer;
	std::vector<double> outbuffer;
};

#endif /* CART_GRID_H_ */
