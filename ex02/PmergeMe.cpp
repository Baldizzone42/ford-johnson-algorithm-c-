/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:31:19 by jormoral          #+#    #+#             */
/*   Updated: 2025/04/21 15:13:37 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){
	this->str = new std::string[3000];
	this->size = 1;
	this->array =  new int[1];
	this->label = new std::string[1];
	
}

PmergeMe::~PmergeMe(){
	delete []str;
	delete []array;
	delete []label;
}

PmergeMe::PmergeMe(PmergeMe *copy){
	this->size = copy->size;
	this->array = new int[this->size];
	for(int i = 0; i < this->size; i++)
		this->array[i] = copy->array[i];
	this->label[0] = copy->label[0];
}


PmergeMe& PmergeMe::operator=(const PmergeMe &other){
	if(this != &other)
		*this = other;	
	return *this;
}

PmergeMe::PmergeMe(const PmergeMe &copy){
	this->size = copy.size;
	this->array = new int[this->size];
	for(int i = 0; i < this->size; i++)
		this->array[i] = copy.array[i];
	this->label[0] = copy.label[0];
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
	return lst;
}