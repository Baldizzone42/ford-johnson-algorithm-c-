/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:06:32 by jormoral          #+#    #+#             */
/*   Updated: 2025/04/21 16:59:26 by jormoral         ###   ########.fr       */
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
	if(lst.size() == 1 || lst.size() > 3000)
		return (std::cout << "Error: Non-orderable number size.\n"), 1;
	std::list<PmergeMe*>::iterator it = lst.begin();
	std::list<PmergeMe*>::iterator itsecond = lst.begin();
	std::list<PmergeMe*>::iterator itend = lst.end(); 
	while(it != itend)
	{
		itsecond = it;
		itsecond++;
		while(itsecond != itend)
		{
			if((*it)->array[0] == (*itsecond)->array[0])
				return (std::cout << "Error: repeated number\n"), 1;
			itsecond++;
		}
		it++;
	}
	return 0;
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


int* fusion_array(PmergeMe *a, PmergeMe *b, size_t npairs)
{
	int *temp = new int[npairs];
	int i = 0;
	size_t j = 0;
	while(i < a->size)
	{
		temp[j] = (*a).array[i];
		i++;
		j++;
	}
	i = 0;
	while(i < b->size)
	{
		temp[j] = (*b).array[i];
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
		itsecond = it;
		itsecond++;
		if(itsecond != itend && (*it)->size == (*itsecond)->size)
		{
			int *arrayy = fusion_array((*it), (*itsecond), npairs);
			PmergeMe *temp = new PmergeMe(npairs);
			temp->array = arrayy;
			result.push_back(temp);
			it++;
		}
		else if(itsecond != itend)
		{
			int *arrayy = fusion_array((*it), (*itsecond), npairs);
			PmergeMe *temp = new PmergeMe((int)((*it)->size  + (*itsecond)->size));
			temp->array = arrayy;
			result.push_back(temp);
			it++;
		}
		else if(itsecond == itend)
		{
			PmergeMe *temp = new PmergeMe((*it));
			result.push_back(temp);
		}
		++it;
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
			(*it)->label = ("b" + bnumber.str());
			b++;
		}
		else if(((*it)->size == (int)npairs) && i % 2 == 0)
		{
			std::ostringstream anumber;
			anumber << a;
			(*it)->label = "a" + anumber.str();
			a++;
		}
		else
			(*it)->label = "Non-participating"; 
		it++;
		i++;
	}
	std::list<PmergeMe*>::iterator itt = sequence.begin();
	std::list<PmergeMe*>::iterator ittend = sequence.end();
	while(itt != ittend)
	{
		std::cout << (*itt)->label << std::endl;
		itt++;
	}
}


bool jacobcheck(std::list<PmergeMe*> sequence)
{
	std::list<PmergeMe*>::iterator it = sequence.begin();
	std::list<PmergeMe*>::iterator itend = sequence.end();
	int x = 0;
	while(it != itend)
	{
		if((*it)->label == "b2")
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
	result[0] = new PmergeMe(npairs);
	result[1] = new PmergeMe(node->size - npairs);
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
	std::list<PmergeMe*>sequence;
	std::cout << "//////////////////Aqui/////////////////////" << std::endl;
	sequence = PmergeMe::init(argv);
	if(check_duplicate(sequence) || check_sintax(sequence))
		return 1;
	

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

		//std::cout << "Size npairs: " << npairs << std::endl;
		newsq = fusion(sequence, npairs);
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
		label(sequence, npairs);
	}
	return 0;
}