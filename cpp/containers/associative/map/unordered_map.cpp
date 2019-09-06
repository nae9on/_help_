/*
 * unordered_map.cpp
 *
 *  Created on: Aug 27, 2019
 *      Author: akadar
 *
 * A std::unordered_map is an associative container that contains key-value pairs with unique keys.
 * Reference
 * [1] http://www.cplusplus.com/reference/unordered_map/unordered_map/
 *
 * Internally, the elements in an unordered_map are not sorted in any particular order with
 * respect to either their key or mapped value, but organized into buckets depending on their
 * hash value to allow for fast access to individual elements directly by their key value.
 *
 * Recall: A hash function is a mapping from a large value space to a much smaller value space.
 * Therefore, a hash function is bound to result into collisions (unless all the keys are known
 * a priori) when multiple keys result into the same hash value. The lookup in this case is not
 * constant time any more i.e. O(1). Worst case look up is O(N) when all the keys will hash into
 * the same bucket.
 *
 * Generally as compared to maps, unordered_map containers are faster for accessing individual
 * elements (assuming constant time look-up). Therefore, for pure lookup they can be preferred
 * over maps. However, when the application requires frequent insertions and deletions, the
 * hashing+bucketing feature will result into performance loss in which case maps are to be
 * preferred. Note that unordered_maps generally use more memory than maps.
 *
 */

#include <iostream>
#include <unordered_map>
#include <functional> //std::hash

int unordered_map(){

	// Note the hash function provided is the default std::hash
	std::unordered_map<int,std::string,std::hash<int>> umap;

	umap.insert(std::make_pair(1989,"Ali"));
	umap.insert(std::make_pair(1993,"Kaynat"));
	umap.insert(std::make_pair(1962,"Mom"));

	// Note that output is not sorted by keys.
	// When unordered_map is changed to map, the output is sorted by keys.
	for(const auto& elem : umap){
		std::cout<<elem.second<<" was born in year "<<elem.first<<"\n";
	}

	return 0;
}
