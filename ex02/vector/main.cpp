/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:40:00 by jormoral          #+#    #+#             */
/*   Updated: 2025/04/30 12:45:10 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


bool digit(char c)
{
	if(c >= '0' && c <= '9')
		return true;
	return false;
}

int check_sintax(std::vector<PmergeMe*>lst)
{
	if(lst.size() == 0 || lst.size() > 3000)
		return (std::cout <<"Non-orderable number size.\n"), 1;
	std::vector<PmergeMe*>::iterator it = lst.begin(); 	
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

int check_duplicate(std::vector<PmergeMe*>lst)
{
	if(lst.size() == 0 || lst.size() > 3000)
		return (std::cout << "Error: Non-orderable number size.\n"), 1;
	std::vector<PmergeMe*>::iterator it = lst.begin();
	std::vector<PmergeMe*>::iterator itsecond = lst.begin();
	std::vector<PmergeMe*>::iterator itend = lst.end(); 
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



void print(std::vector<PmergeMe*>lst)
{
	std::vector<PmergeMe*>::iterator it = lst.begin();
	std::vector<PmergeMe*>::iterator itend = lst.end();
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

void sort(std::vector<PmergeMe*> sequence, size_t npairs)
{ 	
	std::vector<PmergeMe*>::iterator it = sequence.begin();
	std::vector<PmergeMe*>::iterator itsecond = sequence.begin();
	std::vector<PmergeMe*>::iterator itend = sequence.end();
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


std::vector<PmergeMe* >fusion(std::vector<PmergeMe*>sequence, size_t npairs)
{
	std::vector<PmergeMe*> result;
	std::vector<PmergeMe*>::iterator it = sequence.begin();
	std::vector<PmergeMe*>::iterator itsecond = sequence.begin();
	std::vector<PmergeMe*>::iterator itend = sequence.end();
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


void label(std::vector<PmergeMe*>sequence, size_t npairs)
{
	std::vector<PmergeMe*>::iterator it = sequence.begin();
	std::vector<PmergeMe*>::iterator itend = sequence.end();
	int i = 1;
	int a = 1;
	int b = 1;
	while(it != itend)
	{
		if(((*it)->size == (int)npairs) && i % 2 != 0)
		{
			std::ostringstream bnumber;
			bnumber << b;
			(*it)->lbl = b;
			(*it)->label = ("b" + bnumber.str());
			b++;
		}
		else if(((*it)->size == (int)npairs) && i % 2 == 0)
		{
			std::ostringstream anumber;
			anumber << a;
			(*it)->lbl = a;
			(*it)->label = "a" + anumber.str();
			a++;
		}
		else
			(*it)->label = "Non-participating"; 
		it++;
		i++;
	}
	std::vector<PmergeMe*>::iterator itt = sequence.begin();
	std::vector<PmergeMe*>::iterator ittend = sequence.end();
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


std::vector<PmergeMe*>divide(std::vector<PmergeMe*>sequence, size_t npairs)
{
	std::vector<PmergeMe*>::iterator it = sequence.begin();
	std::vector<PmergeMe*>::iterator itend = sequence.end();
	std::vector<PmergeMe*> result;
	
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

std::vector<PmergeMe*> final_jacob(std::vector<PmergeMe*> main, std::vector<PmergeMe*> pend , size_t npairs)
{

	while(pend.size() > 0)
	{	
		std::vector<PmergeMe*>::iterator rev = pend.end();
		//std::cout << VERDE; print(pend);
		rev--;
		//std::cout << MORADO <<(*rev)->array[0] << std::endl;
		//std::cout << "hola" << std::endl;
		//std::cout << AMARILLO; print(main);
		std::vector<PmergeMe*>::iterator it = main.begin();
		std::vector<PmergeMe*>::iterator itend = main.end();
		while(it != itend)
		{
			//std::cout << "Npairs ----------------> " << npairs << std::endl;
			if((*it)->array[npairs - 1] > (*rev)->array[npairs - 1])
			{
			//	std::cout << "ruina" << std::endl;
				main.insert(it, (*rev));
				pend.erase(rev);
				it = main.begin();
				itend = main.end();
				break ;
			}
			it++;
			if(it == main.end())
			{
				main.push_back((*rev));
				return main;
			}
		}	
	}
	
	return main;
}

std::vector<PmergeMe*>jacobsthal_level(std::vector<PmergeMe*> main, std::vector<PmergeMe*> pend, size_t npairs)
{
	std::vector<PmergeMe*>::iterator pet = pend.begin();
	std::vector<PmergeMe*>::iterator petend = pend.end();
	std::vector<PmergeMe*>::iterator it = main.begin();
	std::vector<PmergeMe*>::iterator itend = main.end();
	int level[]  = {1, 3, 5, 11, 21, 43, 85, 171, 341,583, 1365, 2731};
	int x;	
	int i = 1;
	int flag = 0;
	int get_out = 0;
	
	while(pend.size() > 0)
	{
		std::vector<PmergeMe*>::iterator out = pend.begin();
		std::vector<PmergeMe*>::iterator outend = pend.end();
		x = level[i];
		flag = 0;
		get_out = 0;
		std::cout << "X:---------------------> " << x  << " Out.label " << (*out)->lbl << std::endl;
		while(out != outend)
		{ 
			std::cout << "Out.label " << (*out)->lbl << std::endl;
			if((*out)->lbl == x)
				get_out = 1;
			out++;
			if(out == outend && get_out == 0)
				return(final_jacob(main, pend, npairs));
		}
		while(pet != petend && x > level[i - 1])
		{
			if((*pet)->lbl == x)
			{
				//print(main);
				//print(pend);
				std::cout << (*pet)->lbl << std::endl;
				while(it != itend)
				{
					if((*it)->array[npairs - 1] > (*pet)->array[npairs - 1])
					{
						main.insert(it, (*pet));
						pend.erase(pet);
						x--;
						pet = pend.begin();
						petend = pend.end();
						it = main.begin();
						itend = main.end();
						flag = 1;
						break ;
					}
					it++;
					if(it == itend && flag == 0)
					{
						main.push_back((*pet));
						pend.erase(pet);
						pet = pend.begin();
						petend = pend.end();
						break;
					}
				}
			}
			else
				pet++;
		}
		i++;
	}
	return main;
}

		
std::vector<PmergeMe*> jacobsthal(std::vector<PmergeMe*> sequence, size_t npairs)
{
	(void)npairs;
	std::vector<PmergeMe*> main;
	std::vector<PmergeMe*> NP;
	std::vector<PmergeMe*> pend;
	std::vector<PmergeMe*>::iterator it = sequence.begin();
	std::vector<PmergeMe*>::iterator itend = sequence.end();
	std::vector<PmergeMe*>::iterator np;
	
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
	//std::cout << "SIZE MAIN: ----------> " << main.size() << std::endl;
	//std::cout << "SIZE PEND: ----------> " << pend.size() << std::endl;
	if(NP.size() > 0)
	{
		np = NP.begin();
		main.push_back((*np));
		return main;
	}
	//std::cout << ROJO << std::endl, print(main);
	return main;
}


void is_sorted(std::vector<PmergeMe*>sequence)
{
	std::vector<PmergeMe*>::iterator it = sequence.begin();
	std::vector<PmergeMe*>::iterator itend = sequence.end();
	std::vector<PmergeMe*>::iterator itsecond;
	
	while(it != itend)
	{ 
		if(sequence.size() == 1)
			break;
		itsecond = it;
		if(sequence.size() >= 2)
			itsecond++;
		while(itsecond != itend)
		{
			if((*it)->array[0] >= (*itsecond)->array[0])
			{
				std::cout << ROJO << "Not sorted" << std::endl;
				exit(1);
			}
			itsecond++;
		}
		it++;
	}
	std::cout << AMARILLO << "It is ordered" << std::endl;
}



int main(int argc, char **argv)
{
	if(argc == 1 || argv[1][0] == '\0')
		return (std::cerr << "Wrong number of arguments.\n"), 1;
	std::vector<PmergeMe*>sequence;
	sequence = PmergeMe::init(argv);
	if(check_duplicate(sequence) || check_sintax(sequence))
		return 1;
	size_t npairs = 1;
	size_t level = 1;
	std::cout << AZUL << "Our original sequence: \n";
	//sort(sequence, npairs), print(sequence);
	size_t sqinitial = sequence.size();
	while((sqinitial / 2 ) >= npairs)
	{
		std::cout << MORADO << "Start " << level << ": " << std::endl , print(sequence);
		std::cout << VERDE << "Sequence after sorting: \n";
		sort(sequence, npairs), print(sequence);
		npairs = 2 * npairs;
	
		std::vector<PmergeMe*> newsq;
		newsq = fusion(sequence, npairs);
		std::cout  << AZUL << "Fusion " << level++ << ": ", print(newsq);
		sequence = newsq;
	}
	sort(sequence, npairs);
	std::cout << CIAN << "After last sort \n"; print(sequence);
	std::vector<PmergeMe*> jacobsq; ///Jacobsthal se viene
	std::vector<PmergeMe*> test;
	//int flag = 0;	
	/* if(flag == 1)
			break;
		flag++; */
	while(npairs > 0)
	{
		//print(sequence);
		label(sequence, npairs);
		test = jacobsthal(sequence, npairs);
		std::cout << VERDE << "Jacobsthal: " << std::endl, print(test);
		npairs = npairs / 2;
		//std::cout << "npairs:" << npairs << std::endl;
		//std::cout << "N!AAAAAAAAAAAAAaa "<< npairs << std::endl;
		if(npairs == 0)
		{
			is_sorted(test), print(test);
			return 0;
		}	
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