/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:54:57 by jormoral          #+#    #+#             */
/*   Updated: 2025/04/17 20:01:10 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP


#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <cstdlib>


#define ROJO     "\033[31m"
#define VERDE    "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL     "\033[34m"
#define MORADO   "\033[35m"
#define CIAN     "\033[36m"
#define BLANCO   "\033[37m"


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
		int size;
		std::string *label;
		
	private:
	
};



#endif