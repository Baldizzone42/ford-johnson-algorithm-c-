/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:06:32 by jormoral          #+#    #+#             */
/*   Updated: 2025/04/21 15:18:16 by jormoral         ###   ########.fr       */
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
	size_t i = 	0;
	while(i < lst.size())
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
	size_t i = 0;	
	while(i < lst.size())
	{
		size_t j = i + 1;
		while(j < lst.size())
		{
			if((*it)->array[i] == (*it)->array[j])
				return (std::cout << "Error: repeated number\n"), 1;
			j++;
		}
		i++;
	}
	return 0;
}


std::list<PmergeMe*> arraymerge(std::list<PmergeMe*>lst)
{
	std::list<PmergeMe*>result;
	std::list<PmergeMe*>::iterator it = lst.begin();
	size_t i = 0;
	while(i < lst.size())
	{
		PmergeMe *nodo = new PmergeMe;
		nodo->array[0] = (*it)->array[i];
		nodo->str[0] = (*it)->str[i];
		result.push_back(nodo);
		i++;
	}
	return result;
}

void print(std::list<PmergeMe*>lst)
{
	std::list<PmergeMe*>::iterator it = lst.begin();
	std::list<PmergeMe*>::iterator itend = lst.end();
	while(it != itend)
	{
		int i = 0;
		while(i < (*it)->size)
		{
			std::cout << (*it)->array[i] << ".";
			i++;
		}
		std::cout << " // ";
		it++;
	}
	std::cout << std::endl << std::endl;
}

void sort(std::list<PmergeMe*> sequence, size_t npairs)
{ 	
	std::list<PmergeMe*>::iterator it = sequence.begin();
	std::list<PmergeMe*>::iterator itsecond = sequence.begin();
	std::list<PmergeMe*>::iterator itend = sequence.end();
	while(itsecond != itend)
	{
		itsecond++;
		if(itsecond != itend && (*itsecond)->size != (int)npairs)
			break ;
		if(itsecond != itend && (*it)->array[npairs - 1] > (*itsecond)->array[npairs - 1])
		{
			int *temp = (*it)->array;
			(*it)->array = (*itsecond)->array;
			(*itsecond)->array = temp;
		}
		else if(itsecond == itend)
			break;
		it++,it++;
		itsecond++;
	}
}


int* fusion_array(int *a, int *b, size_t npairs)
{
	int *temp = new int[npairs];
	size_t i = 0;
	size_t j = 0;
	while(i < (npairs / 2))
	{
		temp[j] = a[i];
		i++;
		j++;
	}
	i = 0;
	while(i < (npairs / 2))
	{
		temp[j] = b[i];
		i++;
		j++;
	}
	return temp;
}

int* infusion_array(int *a, int size)
{
	int *temp = new int[size];
	int i = 0;
	int j = 0;
	while(i < size)
	{
		temp[j] = a[i];
		i++;
		j++;
	}
	return temp;
}


std::list<PmergeMe* >fusion(std::list<PmergeMe*>sequence, size_t npairs)
{
	std::list<PmergeMe*> result;
	std::list<PmergeMe*>::iterator it = sequence.begin();
	std::list<PmergeMe*>::iterator itsecond = sequence.begin();
	std::list<PmergeMe*>::iterator itend = sequence.end();
	while(it != itend)
	{
		itsecond++;
		if(itsecond != itend)
		{
			//std::cout << (*it)->size << " <-it   tsecond-> " << (*itsecond)->size << std::endl;
			if((*it)->size != (*itsecond)->size)
				(*it)->size += (*itsecond)->size;
			else	
			{
				(*it)->size = npairs;
				(*itsecond)->size = npairs;
			}
			PmergeMe *node = new PmergeMe;
			int *temp = new int[npairs];
			temp = fusion_array((*it)->array, (*itsecond)->array, npairs);
			int i = 0;
			
			while(i < ((*it)->size))
			{
				node->str[i] = (*it)->str[i];
				node->array[i] = temp[i];
				node->size = (*it)->size;
				i++;
			}
			result.push_back(node);
		}
		else if(itsecond == itend)
		{
			int i = 0;
			PmergeMe *node = new PmergeMe;
			int *temp = new int[(*it)->size];
			temp = infusion_array((*it)->array, (*it)->size);
			while(i < (*it)->size)
			{
				node->str[i] = (*it)->str[i];
				node->array[i] = temp[i];
				node->size = (*it)->size;
				i++;
			}
			result.push_back(node);
			return result;
		}
		it++, it++;
		itsecond++;
	}
	return result;
}


void label(std::list<PmergeMe*>sequence, size_t npairs)
{
	std::list<PmergeMe*>::iterator it = sequence.begin();
	std::list<PmergeMe*>::iterator itend = sequence.end();
	int i = 1;
	int a = 1;
	int b = 1;
	while(it != itend)
	{
		//std::cout << (*it)->size << std::endl;
		if(((*it)->size == (int)npairs) && i % 2 != 0)
		{
			//std::to_String no funciona solo en c++11 sus muertos
			std::ostringstream bnumber;
			bnumber << b;
			(*it)->label[0] = ("b" + bnumber.str());
			b++;
		}
		else if(((*it)->size == (int)npairs) && i % 2 == 0)
		{
			std::ostringstream anumber;
			anumber << a;
			(*it)->label[0] = "a" + anumber.str();
			a++;
		}
		else
			(*it)->label[0] = "Non-participating"; 
		it++;
		i++;
	}
	/* std::list<PmergeMe*>::iterator itt = sequence.begin();
	std::list<PmergeMe*>::iterator ittend = sequence.end();
	while(itt != ittend)
	{
		std::cout << (*itt)->label[0] << std::endl;
		itt++;
	} */
}


bool jacobcheck(std::list<PmergeMe*> sequence)
{
	std::list<PmergeMe*>::iterator it = sequence.begin();
	std::list<PmergeMe*>::iterator itend = sequence.end();
	int x = 0;
	while(it != itend)
	{
		if((*it)->label[0] == "b2")
			x++;
		it++;
	}
	if(!x)
		return false;
	return true;
} 



PmergeMe** divide_node(PmergeMe* node, size_t npairs)
{
	PmergeMe **result = new PmergeMe*[2];
	result[0] = new PmergeMe;
	result[1] = new PmergeMe;
	//std::cout << "Npairs: " << npairs << std::endl;
	int i = 0;
	while(i < (int)npairs)
	{
		result[0]->array[i] = node->array[i];
		i++;
	}
	result[0]->size = npairs;
	int c = 0;
	while(i < node->size)
	{
		result[1]->array[c] = node->array[i];
		i++;
		c++;
	}
	result[1]->size = (node->size - npairs);
	return result;
}


std::list<PmergeMe*>divide(std::list<PmergeMe*>sequence, size_t npairs)
{
	std::list<PmergeMe*>::iterator it = sequence.begin();
	std::list<PmergeMe*>::iterator itend = sequence.end();
	std::list<PmergeMe*> result;
	
	while(it != itend)
	{
		if((*it)->size > (int)npairs)
		{
			PmergeMe **temp;
			temp = divide_node((*it), npairs);
			result.push_back(temp[0]);
			result.push_back(temp[1]);
		}
		else
			result.push_back((*it));
		it++;	
	}
	return result;
}

/* std::list<PmergeMe*> jacobsthal(std::list<PmergeMe*> sequence, size_t npairs)
{
	std::list<PmergeMe*> main;
	std::list<PmergeMe*>::iterator it = sequence.begin();
	std::list<PmergeMe*>::iterator itend = sequence.end();
	//making Main jacob
	while(it != itend)
	{
		if((*it)->label[0] == "b1")
		{
			PmergeMe *temp = new PmergeMe((*it));
			main.insert(it,(temp));
			//sequence.erase(it);
			it = sequence.begin();
		}
		else if((*it)->label[0].find('a'))
		{
			PmergeMe *temp = new PmergeMe((*it));
			main.insert(it,(temp));
			//sequence.erase(it);
			it = sequence.begin();
		}
		else
			it++;
	}
	std::list<PmergeMe*>::iterator itpo = main.begin();
	std::list<PmergeMe*>::iterator itendpo = main.end();
	while(itpo != itendpo)
	{
		
		std::cout << (*itpo)->array<< "//";
		itpo++;
		std::cout << "holaaa";
	}
	std::cout << std::endl;
	exit(42);
	
	//insert Pend a Main.
	int jacob[] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731};
	std::list<PmergeMe*>::iterator itp = sequence.begin();
	std::list<PmergeMe*>::iterator itendp = sequence.end();
	int j = 0;
	while(itp != itend)
	{
		
		j++;
		std::ostringstream number;
		number << jacob[j];
		while(itp != itendp && (*itp)->label[0] != "b" + number.str())
		{
			itp++;
			if(itp == itend)
			{
				itp = sequence.begin();
				jacob[j] -= 1;
				number << jacob[j];
				if(jacob[j] == 1)
				{
					//std::cout << "pendejo" << std::endl;
					break;
				}
			}
			else if((*itp)->label[0] == "b" + number.str())
			{
				std::list<PmergeMe*>::iterator mit = main.begin();
				std::list<PmergeMe*>::iterator msecond = main.begin();
				msecond++;
				std::list<PmergeMe*>::iterator mend = main.end();
				while(mit != mend)
				{
					if(((*itp)->array[npairs - 1] > (*mit)->array[npairs -1]) && ((*itp)->array[npairs - 1] < (*msecond)->array[npairs -1]))
					{
						main.insert(msecond, (*itp));
						sequence.erase(itp);
					}
					mit++;
					msecond++;
				}
			}	
		}
		itp++;
	}
	return main;
} */
		
int main(int argc, char **argv)
{
	if(argc == 1)
		return (std::cerr << "Wrong number of arguments.\n"), 1;
	PmergeMe* merge = new PmergeMe();
	std::list<PmergeMe*>lst;
	lst = merge->init(merge, argv);
	if(check_duplicate(lst) || check_sintax(lst))
		return 1;
	std::list<PmergeMe*> sequence = arraymerge(lst);

	size_t npairs = 1;
	size_t level = 1;
	std::cout << AZUL << "Our original sequence: \n", print(sequence);
	while(sequence.size() >= npairs)
	{
		std::cout << MORADO << "Recursion level " << level << ": " << std::endl , print(sequence);
		std::cout << VERDE << "Sequence after sorting: \n";
		sort(sequence, npairs), print(sequence);
		npairs = 2 * npairs;
		std::list<PmergeMe*> newsq;
		newsq = fusion(sequence, npairs);
		//std::cout << "Size npairs: " << npairs << std::endl;
		std::cout  << AZUL << "Fusion " << level++ << ": ", print(newsq);
		sequence = newsq;
	}
	std::list<PmergeMe*> jacobsq; ///Jacobsthal se viene
	while(npairs > 1)
	{
		label(sequence, npairs);
		/* if(jacobcheck(sequence))
		{
			jacobsq = jacobsthal(sequence, npairs);
			std::cout << "ciao jacobo" << std::endl;
			std::cout << VERDE << "Jacobsthal: " << std::endl, print(jacobsq);
		} */
		npairs = npairs / 2;
		if(npairs > 0)
			jacobsq = divide(sequence, npairs);
		std::cout << AMARILLO << "Divide: " << std::endl, print(jacobsq);
		sequence = jacobsq;
	}
	return 0;
}