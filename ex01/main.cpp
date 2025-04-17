/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:54:56 by jormoral          #+#    #+#             */
/*   Updated: 2025/04/09 21:15:24 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int op(char c){
	char op[4] = {'+', '-', '/', '*'};
	for(int i = 0; i < 4; i++){
		if(c == op[i])
			return 1;
	}
	return 0;
}

void RPN::calculate(std::vector<std::string>::iterator it, char c, int i)
{
	(void)it;
	int result = 0;
	if(c == '*')
	{
		result = atoi(this->polish[i - 2].c_str()) * atoi(this->polish[i - 1].c_str());
		std::cout << result << std::endl;
	}
	if(c == '-')
	{
		result = atoi(this->polish[i - 2].c_str()) - atoi(this->polish[i - 1].c_str());
		std::cout << result << std::endl;
	}
	if(c == '/')
	{
		result = atoi(this->polish[i - 2].c_str()) / atoi(this->polish[i - 1].c_str());
		std::cout << result << std::endl;
	}
	if(c == '+')
	{
		result = atoi(this->polish[i - 2].c_str()) + atoi(this->polish[i - 1].c_str());
		std::cout << result << std::endl;
	}
	//result = result + result;
}

void RPN::polish_calculator()
{

	std::vector<std::string>::iterator it = this->polish.begin();
	std::vector<std::string>::iterator itn = this->polish.begin();
	(void)itn;
	int i = 0;
	while(it != this->polish.end())
	{
		if(op((*it)[0]))
		{
			calculate(it, (*it)[0], i);
		}
		i++;
		it++;
	}
		
}



int main(int argc, char **argv)
{
	if(argc != 2)
		return (std::cerr << "Number of erroneous arguments\n"), 1;
	RPN main;
	std::string line = argv[1];
	//std::cout << line << std::endl;
	for(int i = 0; line[i]; i++)
	{
		if((line[i] >= '0' && line[i] <= '9') || line[i] == ' ' || op(line[i]))
			continue;
		else
			return (std::cerr << "invalid character\n"), 1;
	}
	size_t i = 0; // "  9999  99999 *"
	std::string str;
	size_t j = 0;
	while(line[i])
	{
		while(line[j] && line[j] == ' ')
			j++;
		i = j;
		while(line[j] && line[j] != ' ')
			j++;
		if(i != j)
			str = line.substr(i, j - i),main.polish.push_back(str);	
	}
		main.polish_calculator();
/* 	for(size_t i = 0; i < main.polish.size(); i++){
		std::cout << main.polish[i] << ".";
	} */
	return 0;
}