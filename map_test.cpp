#include "test.hpp"
#include "utils.hpp"
#include <map>
#include "Map.hpp"
template <class Key, class T>
void print_std_map(std::map<Key, T> & map){
	typename std::map<Key, T>::const_iterator it = map.begin();
	typename std::map<Key, T>::const_iterator ite = map.end();
	std::cout << "STD Map:" << std::endl;
	while (it != ite){
		std::cout << "key:\t" << it->first << "\t\tvalue:\t" << it->second << std::endl;
		it++;
	}
	std::cout << std::endl;
}

template <class Key, class T>
void print_ft_map(ft::map<Key, T> & map){
	typename ft::map<Key, T>::const_iterator it = map.begin();
	// std::cout<<"check"<<std::endl;
	typename ft::map<Key, T>::const_iterator ite = map.end();
	std::cout << "FT Map:" << std::endl;
	while (it != ite){
		std::cout << "key:\t" << it->first << "\t\tvalue:\t" << it->second << std::endl;
		it++;
	}
	std::cout << std::endl;
}

void map_test(){
	std::cout << "---------------------" << std::endl;
	std::cout << "      MAP TESTS      " << std::endl;
	std::cout << "---------------------" << std::endl << std::endl;

	ft::map<int, int> ft_map;
	std::map<int, int> std_map;

	ft_map.insert(ft::pair<const int, int>(5, 10));
	ft_map.insert(ft::pair<const int, int>(3, 11));
	ft_map.insert(ft::pair<const int, int>(10, 11));
	ft_map.insert(ft::pair<const int, int>(6, 11));
	// std::cout << ft_map.size() << std::endl;

	std_map.insert(std::pair<const int, int>(5, 10));
	std_map.insert(std::pair<const int, int>(3, 11));
	std_map.insert(std::pair<const int, int>(10, 11));
	std_map.insert(std::pair<const int, int>(6, 11));
	// std::cout << std_map.size() << std::endl;

	std::cout << "Empty Constructor and insert single elements" << std::endl;
	print_ft_map(ft_map);
	print_std_map(std_map);

	ft::map<int, int> ft_map2(++ft_map.begin(), --ft_map.end());
	std::map<int, int> std_map2(++std_map.begin(), --std_map.end());
	std::cout << "Constructor with iterators" << std::endl;
	print_ft_map(ft_map2);
	print_std_map(std_map2);

	ft::map<int, int> ft_map3(ft_map2);
	std::map<int, int> std_map3(std_map2);
	std::cout << "Copy constructor" << std::endl;
	print_ft_map(ft_map3);
	print_std_map(std_map3);

	ft_map3.clear();
	std_map3.clear();
	std::cout << "After Clear function" << std::endl;
	print_ft_map(ft_map3);
	print_std_map(std_map3);

	std::cout << "Empty function on empty maps" << std::endl;
	std::cout << "FT map: " << ft_map3.empty() << std::endl;
	std::cout << "STD map: " << std_map3.empty() << std::endl;

	std::cout << std::endl << "Empty function on non-empty maps" << std::endl;
	std::cout << "FT map: " << ft_map2.empty() << std::endl;
	std::cout << "STD map: " << std_map2.empty() << std::endl;

	std::cout << std::endl << "Size function" << std::endl;
	std::cout << "FT map: " << ft_map2.size() << std::endl;
	std::cout << "STD map: " << std_map2.size() << std::endl;

	std::cout << std::endl << "[5] operator" << std::endl;
	std::cout << "FT map: " << ft_map[5] << std::endl;
	std::cout << "STD map: " << std_map2[5] << std::endl;

	std::cout << std::endl << "Insert with hints" << std::endl;
	ft_map.insert(++ft_map.begin(), ft::pair<const int, int>(30, 5));
	std_map.insert(++std_map.begin(), std::pair<const int, int>(30, 5));
	print_ft_map(ft_map);
	print_std_map(std_map);

	ft_map2.insert(ft::pair<const int, int>(-10, -5));
	std_map2.insert(std::pair<const int, int>(-10, -5));
	std::cout << std::endl << "Insert with iterators with already existing elements" << std::endl;
	ft_map.insert(ft_map2.begin(), ft_map2.end());
	std_map.insert(std_map2.begin(), std_map2.end());
	print_ft_map(ft_map);
	print_std_map(std_map);

	std::cout << std::endl << "Erase with single iterator" << std::endl;
	ft_map.erase(++ft_map.begin());
	std_map.erase(++std_map.begin());
	print_ft_map(ft_map);
	print_std_map(std_map);

	std::cout << std::endl << "Erase by key" << std::endl;
	ft_map.erase(6);
	std_map.erase(6);
	print_ft_map(ft_map);
	print_std_map(std_map);

	std::cout << std::endl << "Erase non-existing key" << std::endl;
	ft_map.erase(300);
	std_map.erase(300);
	print_ft_map(ft_map);
	print_std_map(std_map);

	std::cout << std::endl << "Erase with iterator range" << std::endl;
	ft_map.erase(++ft_map.begin(), --ft_map.end());
	std_map.erase(++std_map.begin(), --std_map.end());
	print_ft_map(ft_map);
	print_std_map(std_map);

	std::cout << std::endl << "Maps before swap" << std::endl;
	print_ft_map(ft_map2);
	print_std_map(std_map2);

	ft_map2.swap(ft_map);
	std_map2.swap(std_map);

	std::cout << std::endl << "Maps after swap" << std::endl;
	print_ft_map(ft_map2);
	print_std_map(std_map2);

	std::cout << std::endl << "Find(-10)" << std::endl;
	std::cout << "FT Map:\t\tkey:\t" << ft_map.find(-10)->first << "\t\tvalue:\t" << ft_map.find(-10)->second << std::endl;
	std::cout << "STD map:\tkey:\t" << std_map.find(-10)->first << "\t\tvalue:\t" << std_map.find(-10)->second << std::endl;

	std::cout << std::endl << "Count(1)" << std::endl;
	std::cout << "FT Map:\t\t" << ft_map.count(1) << std::endl;
	std::cout << "STD map:\t" << std_map.count(1) << std::endl;

	std::cout << std::endl << "Lower bound(4)" << std::endl;
	std::cout << "FT Map:\t\tkey:\t" << ft_map.lower_bound(4)->first << "\t\tvalue:\t" << ft_map.lower_bound(4)->second << std::endl;
	std::cout << "STD map:\tkey:\t" << std_map.lower_bound(4)->first << "\t\tvalue:\t" << std_map.lower_bound(4)->second << std::endl;

	std::cout << std::endl << "Upper bound(-20)" << std::endl;
	std::cout << "FT Map:\t\tkey:\t" << ft_map.upper_bound(-20)->first << "\t\tvalue:\t" << ft_map.upper_bound(-20)->second << std::endl;
	std::cout << "STD map:\tkey:\t" << std_map.upper_bound(-20)->first << "\t\tvalue:\t" << std_map.upper_bound(-20)->second << std::endl;

	std::cout << std::endl << "Equal range(5)" << std::endl;
	std::cout << "FT Map first iterator:\t\tkey:\t" << ft_map.equal_range(5).first->first << "\t\tvalue:\t" << ft_map.equal_range(5).first->second << std::endl;
	std::cout << "FT Map second iterator:\t\tkey:\t" << ft_map.equal_range(5).second->first << "\t\tvalue:\t" << ft_map.equal_range(5).second->second << std::endl;

	std::cout << "STD Map first iterator:\t\tkey:\t" << std_map.equal_range(5).first->first << "\t\tvalue:\t" << std_map.equal_range(5).first->second << std::endl;
	std::cout << "FT Map second iterator:\t\tkey:\t" << std_map.equal_range(5).second->first << "\t\tvalue:\t" << std_map.equal_range(5).second->second << std::endl;

	std::cout << std::endl << "== operator" << std::endl;
	std::cout << "FT Map\t\t" << (ft_map == ft_map2) << std::endl;
	std::cout << "STD Map\t\t" << (std_map == std_map2) << std::endl;

	std::cout << std::endl << "!= operator" << std::endl;
	std::cout << "FT Map\t\t" << (ft_map != ft_map2) << std::endl;
	std::cout << "STD Map\t\t" << (std_map != std_map2) << std::endl;

	std::cout << std::endl << "> operator" << std::endl;
	std::cout << "FT Map\t\t" << (ft_map > ft_map2) << std::endl;
	std::cout << "STD Map\t\t" << (std_map > std_map2) << std::endl;

	std::cout << std::endl << ">= operator" << std::endl;
	std::cout << "FT Map\t\t" << (ft_map >= ft_map2) << std::endl;
	std::cout << "STD Map\t\t" << (std_map >= std_map2) << std::endl;

	std::cout << std::endl << "< operator" << std::endl;
	std::cout << "FT Map\t\t" << (ft_map < ft_map2) << std::endl;
	std::cout << "STD Map\t\t" << (std_map < std_map2) << std::endl;

	std::cout << std::endl << "<= operator" << std::endl;
	std::cout << "FT Map\t\t" << (ft_map <= ft_map2) << std::endl;
	std::cout << "STD Map\t\t" << (std_map <= std_map2) << std::endl;
	std::cout << std::endl;
}