/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:54:57 by jormoral          #+#    #+#             */
/*   Updated: 2025/05/09 20:21:30 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP


#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#define INTMAX 2147483647 

#define R     "\033[31m"
#define G    "\033[32m"
#define Y "\033[33m"
#define B    "\033[34m"
#define P  "\033[35m"
#define C    "\033[36m"
#define W   "\033[37m"


class PmergeMe
{
	
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe &copy);
		PmergeMe& operator=(const PmergeMe &other);
		PmergeMe(PmergeMe *copy);
		PmergeMe(size_t n);
		
		static std::list<PmergeMe*> init(char **argv);
		int *array;
		int size;
		std::string label;
		int lbl;
		
	private:
};

#endif