/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:06:32 by jormoral          #+#    #+#             */
/*   Updated: 2025/04/23 18:00:35 by jormoral         ###   ########.fr       */
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
		if(((*it)->size == (int)npairs) && i % 2 != 0)
		{
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


PmergeMe** divide_node(PmergeMe* node, size_t npairs)
{
	PmergeMe **result = new PmergeMe*[2];
	result[0] = new PmergeMe(npairs);
	result[1] = new PmergeMe(node->size - npairs);
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


std::list<PmergeMe*>jacobsthal_level(std::list<PmergeMe*> main, std::list<PmergeMe*> pend, size_t npairs)
{
	int level[]  = {1, 3, 5, 11, 21, 43, 85, 171, 341,583, 1365, 2731};
	//char *str[] = {"1", "3", "5", "11", "21", "43", "85", "171", "341", "583", "1365", "2731"};
	int l = 0; /// vamos a reducirlo
	int lvl  = 0; /// y lvl va a mantener el lvl jacobsthal
	int flag = 0;
	std::list<PmergeMe*>::iterator pet = pend.begin();
	std::list<PmergeMe*>::iterator petend = pend.end();
	//std::list<PmergeMe*>::reverse_iterator rever = pend.rend(); //reverse iterator
	while(pend.size() > 0)
	{
		l++, lvl++;
		flag = 0;
		while(pet != petend && level[l] > 1)
		{
			std::list<PmergeMe*>::iterator it = main.begin();
			std::list<PmergeMe*>::iterator itend = main.end();
			std::ostringstream ilv;
			ilv << level[l];
			//std::cout <<  ilv.str() << std::endl;
			std::string n = ("b" + ilv.str());
			if((*pet)->label == n)
			{
				//std::cout << n << std::endl;
				std::cout << (*pet)->label << std::endl;
				while(it != itend)
				{
					if((*it)->array[npairs - 1] > (*pet)->array[npairs - 1])
					{
						
						main.insert(it, (*pet));//// supuesta mente encontrado activar flag, si no recudir l y seguir
						pend.erase(pet);/// eliminamos la posicion una vez encontrada
						l--; 
						pet = pend.begin();
						petend = pend.end();
						//ilv << level[l];
						flag = 1;
						//std::cout << (*pet)->label <<  ("b" + ilv.str()) << std::endl;
						break;	
						
					}
					it++;
				}
			}
			pet++;
			if(pend.size() == 0)
				return main;
			if((pet == petend && pend.size() > 0) || flag == 1)
			{
				pet = pend.begin();
				petend = pend.end();
				l--;
				/* std::cout << level[l] << std::endl;
				std::cout << MORADO << "Main: ", print(main);
				std::cout << MORADO << "Pend: ", print(pend); */
			}
			if(l <= 0)
				break;
		}
		l = lvl;
		//std::cout << "holi "<< l << std::endl;
	}
	
	return main;
}

		
std::list<PmergeMe*> jacobsthal(std::list<PmergeMe*> sequence, size_t npairs)
{
	(void)npairs;
	std::list<PmergeMe*> main;
	std::list<PmergeMe*> NP;
	std::list<PmergeMe*> pend;
	std::list<PmergeMe*>::iterator it = sequence.begin();
	std::list<PmergeMe*>::iterator itend = sequence.end();
	std::list<PmergeMe*>::iterator np;
	//// Añadimos los nodos que corresponde tanto a Main, Pend & Non-participating
	while(it != itend && (*it)->size == (int)npairs)
	{
		if((*it)->label == "b1" || (*it)->label[0] == 'a')
			main.push_back((*it));
		else if((*it)->label[0] == 'b')
			pend.push_back((*it));	
		it++;
	}
	if(it != itend)
		NP.push_back((*it));
	if(pend.size() > 0)
	{
		std::cout << "entra: jacobsthal_level  " << pend.size() << std::endl; 
		std::cout << MORADO << "Main: ", print(main);
		std::cout << MORADO << "Pend: ", print(pend);
		std::cout << MORADO << "Non-P: ", print(NP);
		std::cout << "-------------------------" << std::endl;
		main = jacobsthal_level(main, pend, npairs);   
		//std::cout << AMARILLO <<"AFTER JACOBSTHAL_LEVEL " << std::endl, print(main);                                     
	}
	if(NP.size() > 0)
	{
		np = NP.begin();
		main.push_back((*np));
		return main;
	}
	
	return main;
}


int main(int argc, char **argv)
{
	if(argc == 1)
		return (std::cerr << "Wrong number of arguments.\n"), 1;
	std::list<PmergeMe*>sequence;
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

		newsq = fusion(sequence, npairs);
		std::cout  << AZUL << "Fusion " << level++ << ": ", print(newsq);
		sequence = newsq;
	}
	std::list<PmergeMe*> jacobsq; ///Jacobsthal se viene
	std::list<PmergeMe*> test;
	//int flag = 0;	
	/* if(flag == 1)
			break;
		flag++; */
	while(npairs > 1)
	{
		label(sequence, npairs);
		test = jacobsthal(sequence, npairs);
		std::cout << VERDE << "Jacobsthal: " << std::endl, print(test);
		npairs = npairs / 2;
		if(npairs > 0)
			jacobsq = divide(test, npairs);
		std::cout << AMARILLO << "Divide: " << std::endl, print(jacobsq);
		sequence = jacobsq;
		std::cout << MORADO << "SECUENCE SORT! " << std::endl, print(sequence);
		/*std::cout << MORADO << "Pend: ", print(pend);
		std::cout << MORADO << "Non-P: ", print(NP);
		std::cout << "-------------------------" << std::endl; */
	}
	return 0;
}