/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:56:31 by jormoral          #+#    #+#             */
/*   Updated: 2025/05/01 20:47:33 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(){
}


RPN::~RPN(){
}

RPN::RPN(const RPN &copy){
	*this = copy;
}

RPN& RPN::operator=(const RPN &other){

	if(this == &other)
		return *this;
	else
		*this = other;
	return *this;
}
