/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:54:08 by jormoral          #+#    #+#             */
/*   Updated: 2025/04/09 19:00:06 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void BitcoinExchange::readcsv(BitcoinExchange &store)
{
	std::ifstream csv("data.csv");
	if(!csv.is_open()){
		std::cerr << "Error opening file\n"; exit (1);}
	std::getline(csv, store.str, '\n');
	while(std::getline(csv, store.str, '\n'))
	{
		size_t start = 0;
		size_t dlt = store.str.find(',');
		size_t end = store.str.find('\n');
		std::string date = store.str.substr(start, dlt - start);
		std::string value = store.str.substr(dlt + 1, end - 1);
		store.csv[date] = atof(value.c_str());
	}
	for (std::map<std::string, float>::iterator it = store.csv.begin(); it != store.csv.end(); ++it) {    
		std::cout << "Fecha:" << it->first << ". Valor:" << it->second  << "."<< std::endl;
	}
}
int parse_date(std::string line)
{
	int n = 0;
	int under = 0;
	int i = 0;
	int pipe = 0;
	while(line[i] && line[i] != '|')
	{
		if((line[i] >= '0' && line[i] <= '9' ) || line[i] == '-')
		{
			if(line[i] == '-')
				under++;
			else
				n++;			
		}
		i++;
	}
	if(line[i] == '|' && line[i + 1])
			pipe++;
	if(n == 8 && under == 2 && pipe == 1 && i == 11)
		return 0;
	return(std::cout << "Error: Bad date => " + line + "\n"), 1;
}

bool isdigit(char c)
{
	if(c >= '0' && c <= '9')
		return true;
	return false;
}

int parse_amount(std::string line)
{
	std::string amount = line.substr(13 , line.length());
	int dot = 0;
	if(amount[0] == '\0')
		return(std::cout << "Error: Missing amount of bitcoins\n"), 1;
	//std::cout << "Amount:" << amount + "." <<std::endl;
	for(int i = 0; amount[i]; i++)
	{
		if(amount[i] == '.' && isdigit(amount[i + 1]) && isdigit(amount[i - 1]))
			i++,dot++;
		if(amount[i] < '0' || amount[i] > '9' || dot > 1)
			return (std::cout << "Error: Bad amount of bitcoins => " + line + "\n"), 1;
	}
	float n = atof(amount.c_str());
	if(n > 1000 || n < 0) 
		return(std::cout <<"Error: Bad amount of bitcoins => " + line + "\n"), 1;
	//std::cout << n << std::endl;
	return 0;
}

double BitcoinExchange::ex_rate(std::string fulldate)
{
	std::map<std::string, float>::iterator it = this->csv.begin();
	std::map<std::string, float>::iterator itend = this->csv.end();
	std::map<std::string, float>::iterator itupper = this->csv.upper_bound(fulldate);

	if(itend == itupper)
	{
		itend--;
		if(fulldate == itend->first)
			return itend->second;
	}
	while(it != itupper)
		it++;
	it--;
	return it->second;
}

int BitcoinExchange::parse_line(std::string line)
{
	int famount = -1;
	int fdate = parse_date(line);
	if(!fdate)
		famount = parse_amount(line);
	std::string date[4];
	int array[3];
	if(!fdate && !famount)
	{	
		date[0] = line.substr(0, 4);
		array[0] = atof(date[0].c_str());
		date[1] = line.substr(5, 2);
		array[1] = atof(date[1].c_str());
		date[2] = line.substr(8, 2);
		array[2] = atof(date[2].c_str());
		date[3] = line.substr(13, line.length());
		
		if(array[0] < 2009 ||(array[0] == 2009 && array[1] == 1  && array[2] < 2))
			return 1;
		if(array[1] > 12 || array[1] < 1)
			return 1; 
		int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		int bisi = 0;
		if((array[0] % 4 == 0 && array[0] % 100 != 0) || array[0] % 400 == 0)
			if(array[1] == 2)
				bisi++;
		if(array[2] > days[array[1] - 1] + bisi) 
			return 1;
		std::string fulldate = date[0] + "-" + date[1] + '-' + date[2];
			//std::cout << fulldate << "." <<std::endl;
		
		std::cout << fulldate << " => " << date[3] << " = ";
		std::cout << (atof(date[3].c_str()) * ex_rate(fulldate)) <<  std::endl;
		/* std::cout << "Year:" << date[0];
		std::cout << " Monthl:" << date[1];
		std::cout << " Day:" << date[2];
		std::cout << " Value:" << array[3] << std::endl; */
	}
	return 0;
}

void BitcoinExchange::parse_input(char *s1, BitcoinExchange &store)
{
	std::ifstream input(s1);
	if(input.fail())
	{
		std::cerr << "Error: Could not open " + (std::string)s1 << std::endl;
		return;
	}
	std::string infile;
	(void)store;
	int i = 0;
	while(std::getline(input, infile, '\n'))
	{
		if((infile == "date | value" && i == 0) || infile[0] == '\0')
			continue;
		else if(store.parse_line(infile))
			std::cout << "Date Impossible\n";
		i++;
	}
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		std::cerr << "Error: could not open file.\n";
		return 1;
	}
	(void)argv;
	BitcoinExchange store;
	store.readcsv(store);
	store.parse_input(argv[1], store);
	/////store.csv.upper_bound
	
	return 0;
}