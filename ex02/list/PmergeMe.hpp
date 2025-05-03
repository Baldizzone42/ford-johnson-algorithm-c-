/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:54:57 by jormoral          #+#    #+#             */
/*   Updated: 2025/05/03 18:38:08 by jormoral         ###   ########.fr       */
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