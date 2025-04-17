/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:31:19 by jormoral          #+#    #+#             */
/*   Updated: 2025/04/17 20:20:11 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){
	this->str = new std::string[3000];
	this->array =  new int[3000];
	this->label = new std::string[2];
	this->size = 1;
	
}

PmergeMe::~PmergeMe(){
	delete []str;
	delete []array;
	delete []label;
}



PmergeMe::PmergeMe(const PmergeMe &copy){
	(void)copy;
}

PmergeMe& PmergeMe::operator=(const PmergeMe &other){
	//std::cout << "+++++++++++++++++++++++++++++++++++BACALOA\n";
	(void)other;
	return *this;
}


std::list<PmergeMe*> PmergeMe::init(PmergeMe* merge, char **argv)
{
	(void)merge;
	std::list<PmergeMe*>lst;
	
	int i = 1;
	int j = 0;
	while(argv[i])
	{
		std::string s = argv[i];
		this->str[j] = s;
		int *temp = new int[1];
		temp[0] = atoi(s.c_str());
		this->array[j] = temp[0];
		lst.push_back(this);
		i++;
		j++;
	}
	/* std::list<PmergeMe*>::iterator it = lst.begin();
	std::list<PmergeMe*>::iterator itend = lst.end();
 	int h = 0;
	while(it != itend )
	{
		std::cout << (*it)->array[h] << " ";
		std::cout << (*it)->str[h] << ",";
		it++;
		h++;
	}	
	std::cout << std::endl; */
	return lst;
}