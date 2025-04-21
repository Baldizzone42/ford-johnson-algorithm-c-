/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:31:19 by jormoral          #+#    #+#             */
/*   Updated: 2025/04/21 16:41:51 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){
	this->str = new std::string[3000];
	this->size = 1;
	this->array =  new int[1];
	this->label = "";
	
}

PmergeMe::PmergeMe(size_t n){
	this->str = new std::string[3000];
	this->size = n;
	this->array =  new int[n];
	this->label = "";
	
}

PmergeMe::~PmergeMe(){
	delete []str;
	delete []array;
}

PmergeMe::PmergeMe(PmergeMe *copy){
	this->size = copy->size;
	this->array = new int[this->size];
	for(int i = 0; i < this->size; i++)
		this->array[i] = copy->array[i];
	this->label = copy->label;
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
	this->label = copy.label;
}

std::list<PmergeMe*> PmergeMe::init (char **argv)
{
	std::list<PmergeMe*>lst;
	int i = 1;
	int j = 0;
	while(argv[i])
	{
		PmergeMe *temp = new PmergeMe();
		std::string s = argv[i];
		temp->str[j] = s;
		temp->array[0] = atoi(s.c_str());
		lst.push_back(temp);
		i++;
		j++;
	}
	return lst;
}