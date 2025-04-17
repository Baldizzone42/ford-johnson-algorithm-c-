/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:31:19 by jormoral          #+#    #+#             */
/*   Updated: 2025/04/17 12:37:43 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){
	this->str = new std::string[3000];
	this->array =  new int[3000];
}

PmergeMe::~PmergeMe(){
	delete []str;
	delete []array;
}



PmergeMe::PmergeMe(const PmergeMe &copy){
	(void)copy;
}

PmergeMe& PmergeMe::operator=(const PmergeMe &other){
	(void)other;
	return *this;
}







std::list<PmergeMe*> PmergeMe::init(PmergeMe* merge, char **argv)
{
	(void)merge;
	std::list<PmergeMe*>lst;
	
	int i = 1;
	while(argv[i])
	{
		std::string s = argv[i];
		this->str[i] = s;
		int *temp = new int[1];
		temp[0] = atoi(s.c_str());
		this->array[i] = temp[0];
		lst.push_back(this);
		i++;
	}
	/*std::list<PmergeMe*>::iterator it = lst.begin();
	std::list<PmergeMe*>::iterator itend = lst.end();
 	int j = 0;
	while(it != itend )
	{
		std::cout << (*it)->array[j] << " ";
		std::cout << (*it)->str[j] << ",";
		it++;
		j++;
	}	
	std::cout << std::endl; */
	return lst;
}