/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:06:32 by jormoral          #+#    #+#             */
/*   Updated: 2025/04/17 12:30:52 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


bool digit(char c)
{
	if(c >= '0' && c <= '9')
		return true;
	return false;
}

int check_sintax(std::list<PmergeMe*>lst)
{
	if(lst.size() == 1 || lst.size() >= 3000)
		return (std::cout <<"Non-orderable number size.\n"), 1;
	std::list<PmergeMe*>::iterator it = lst.begin(); 	
	size_t i = 	1;
	while(i <= lst.size())
	{
		int j = 0;
		while((*it)->str[i][j])
		{
			if(digit((*it)->str[i][j]) == false)
				return (std::cout << "Error: Non-numeric character found"), 1;
			j++;
		}
		i++;
	}
	return 0;
}


int check_duplicate(std::list<PmergeMe*>lst)
{
	if(lst.size() == 1 || lst.size() >= 3000)
		return (std::cout <<"Error: Non-orderable number size.\n"), 1;
	std::list<PmergeMe*>::iterator it = lst.begin(); 
	size_t i = 1;	
	while(i <= lst.size())
	{
		size_t j = i + 1;;
		while(j <= lst.size())
		{
			if((*it)->array[i] == (*it)->array[j])
				return (std::cout << "Error: repeated number\n"), 1;
			j++;
		}
		i++;
	}
	return 0;
}



int main(int argc, char **argv)
{
	if(argc == 1)
		return (std::cerr << "Wrong number of arguments.\n"), 1;
	PmergeMe *merge = new PmergeMe();
	std::list<PmergeMe*>lst;
	lst = merge->init(merge, argv);
	if(check_duplicate(lst) || check_sintax(lst))
		return 1;
/* 	size_t size_og = lst.size();
	std::cout << size_og << std::endl;
	size_t npairs = 1;
	int level = 0; */
	std::list<PmergeMe*>::iterator it = lst.begin();
	std::list<PmergeMe*>::iterator itscond = lst.begin();
	//std::list<PmergeMe*>::iterator itend = lst.end();
	++itscond;
	std::cout << (*it)->array[1] << std::endl;
	std::cout << (*itscond)->array[1] << std::endl;
	/* while(size_og >= npairs)
	{
		level++;
		//sort(lst, npairs);
		//recursion_level(merge, lst);
		
	} */
	return 0;
}