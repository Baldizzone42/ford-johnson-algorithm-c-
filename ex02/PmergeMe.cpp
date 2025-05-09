/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:31:19 by jormoral          #+#    #+#             */
/*   Updated: 2025/05/09 20:15:19 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){
	this->size = 1;
	this->array =  new int[1];
	this->label = "";
	this->lbl = 0;
	
}

PmergeMe::PmergeMe(size_t n){
	this->size = n;
	this->array =  new int[n];
	this->label = "";
	this->lbl = 0;
	
}

PmergeMe::~PmergeMe(){
	delete []array;
}


PmergeMe::PmergeMe(PmergeMe *copy){
	this->size = copy->size;
	this->array = new int[this->size];
	for(int i = 0; i < this->size; i++)
		this->array[i] = copy->array[i];
	this->label = copy->label;
	this->lbl = copy->lbl;
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
	this->lbl = copy.lbl;
}

std::list<PmergeMe*> PmergeMe::init(char **argv)
{
	std::list<PmergeMe*>lst;
	int i = 1;
	int j = 0;
	while(argv[i])
	{
		PmergeMe *temp = new PmergeMe();
		std::string s = argv[i];
		temp->array[0] = atoi(s.c_str());
		lst.push_back(temp);
		i++;
		j++;
	}
	return lst;
}
