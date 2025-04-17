/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:54:57 by jormoral          #+#    #+#             */
/*   Updated: 2025/04/17 12:37:31 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP


#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <cstdlib>


class PmergeMe
{
	
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe &copy);
		PmergeMe& operator=(const PmergeMe &other);
	
		std::list<PmergeMe*> init(PmergeMe* merge, char **argv);

		
		int *array;
		std::string *str;
		size_t size;
		
	private:
	
};



#endif