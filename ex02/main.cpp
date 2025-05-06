/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:06:32 by jormoral          #+#    #+#             */
/*   Updated: 2025/05/06 18:20:06 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


bool digit(char c)
{
	if(c >= '0' && c <= '9')
		return true;
	return false;
}

void free_lst(std::list<PmergeMe*>lst)
{
	std::list<PmergeMe*>::iterator it = lst.begin();
	std::list<PmergeMe*>::iterator itend = lst.end();
	while(it != itend)
	{
		delete ((*it));
		it = lst.erase(it);
	}
	lst.clear();
}

int check_sintax(std::list<PmergeMe*>lst, char **argv)
{
	if(lst.size() == 1 || lst.size() > 3000)
		return (std::cout <<"Non-orderable number size.\n"), free_lst(lst),  1;	
	size_t i = 	1;
	while(argv[i])
	{
		int j = 0;
		long maxint = std::atol(argv[i]);
		if(maxint > INTMAX)
			return (std::cout <<"Number too big.\n"), free_lst(lst),  1; 
		while(argv[i][j])
		{
			if(digit(argv[i][j]) == false)
				return (std::cout << "Error: Non-numeric character found\n"), free_lst(lst), 1;
			j++;
		}
		i++;
	}
	return 0;
}

int check_duplicate(std::list<PmergeMe*>lst)
{
	if(lst.size() == 0 || lst.size() > 3000)
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
				return (std::cout << "Error: repeated number\n"), free_lst(lst), 1;
			itsecond++;
		}
		it++;
	}
	return 0;
}

void print(std::list<PmergeMe*>lst)
{
	if(lst.empty())
		return;
	std::list<PmergeMe*>::iterator it = lst.begin();
	std::list<PmergeMe*>::iterator itend = lst.end();
	while(it != itend)
	{
		int i = 0;
		while(i < (*it)->size)
		{
			std::cout << (*it)->array[i];
			i++;
		}
		std::cout << " ";
		it++;
	}
	std::cout << std::endl;
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
			delete []temp->array;
			temp->array = arrayy;
			result.push_back(temp);
			delete (*it);
            delete (*itsecond);
            it = ++itsecond;
            if(it == itend) break;
		}
		else if(itsecond != itend)
		{
			int *arrayy = fusion_array((*it), (*itsecond), npairs);
			PmergeMe *temp = new PmergeMe((int)((*it)->size  + (*itsecond)->size));
			delete []temp->array;
			temp->array = arrayy;
			result.push_back(temp);
			delete (*it);
            delete (*itsecond); 
            it = ++itsecond;
            if(it == itend) 
				break;
		}
		else if(itsecond == itend)
		{
			PmergeMe *temp = new PmergeMe((*it));
			result.push_back(temp);
			delete(*it);
			it++;
		}
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
			result.push_back(new PmergeMe(temp[0]));
			result.push_back(new PmergeMe(temp[1]));
			delete temp[0], delete temp[1];
			delete []temp;
			delete (*it);
		}
		else
			result.push_back((*it));
		it++;	
	}
	return result;
}

std::list<PmergeMe*> final_jacob(std::list<PmergeMe*> main, std::list<PmergeMe*> pend , size_t npairs)
{

	while(pend.size() > 0)
	{	
		std::list<PmergeMe*>::iterator rev = pend.end();
		rev--;
		std::list<PmergeMe*>::iterator it = main.begin();
		std::list<PmergeMe*>::iterator itend = main.end();
		while(it != itend)
		{
			if((*it)->array[npairs - 1] > (*rev)->array[npairs - 1])
			{
				PmergeMe *temp = new PmergeMe((*rev));
				main.insert(it, temp);
				delete (*rev);
				pend.erase(rev);
				it = main.begin();
				itend = main.end();
				break ;
			}
			it++;
			if(it == main.end())
			{
				PmergeMe *temp = new PmergeMe((*rev));
				main.push_back(temp);
				delete (*rev);
				return main;
			}
		}	
	}
	free_lst(pend);
	return main;
}

std::list<PmergeMe*>jacobsthal_level(std::list<PmergeMe*> main, std::list<PmergeMe*> pend, size_t npairs)
{
	std::list<PmergeMe*>::iterator pet = pend.begin();
	std::list<PmergeMe*>::iterator petend = pend.end();
	std::list<PmergeMe*>::iterator it = main.begin();
	std::list<PmergeMe*>::iterator itend = main.end();
	int level[]  = {1, 3, 5, 11, 21, 43, 85, 171, 341,583, 1365, 2731};
	int x;	
	int i = 1;
	int flag = 0;
	int get_out = 0;
	while(pend.size() > 0)
	{
		std::list<PmergeMe*>::iterator out = pend.begin();
		std::list<PmergeMe*>::iterator outend = pend.end();
		x = level[i];
		flag = 0;
		get_out = 0;

		while(out != outend)
		{ 
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
				while(it != itend)
				{
					if((*it)->array[npairs - 1] > (*pet)->array[npairs - 1])
					{
						PmergeMe *temp = new PmergeMe((*pet));
						main.insert(it, temp);
						delete ((*pet));
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
						PmergeMe *temp = new PmergeMe((*pet));
						main.push_back(temp);
						delete ((*pet));
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
	free_lst(pend);
	return main;
}
	
std::list<PmergeMe*> jacobsthal(std::list<PmergeMe*> sequence, size_t npairs)
{
	std::list<PmergeMe*> main;
	std::list<PmergeMe*> NP;
	std::list<PmergeMe*> pend;
	std::list<PmergeMe*>::iterator it = sequence.begin();
	std::list<PmergeMe*>::iterator itend = sequence.end();
	std::list<PmergeMe*>::iterator np;
	while(it != itend && (*it)->size == (int)npairs)
	{
		if((*it)->label == "b1" || (*it)->label[0] == 'a')
		{
			PmergeMe *temp = new PmergeMe((*it));
			main.push_back(temp);
		}
		else if((*it)->label[0] == 'b')
		{
			PmergeMe *temp = new PmergeMe((*it));
			pend.push_back(temp);
		}
		it++;
	}
	if(it != itend)
	{
		PmergeMe *temp = new PmergeMe((*it));
		NP.push_back(temp);
	}
	if(pend.size() > 0)
		main = jacobsthal_level(main, pend, npairs);                             
	if(NP.size() > 0)
	{
		np = NP.begin();
		PmergeMe *temp = new PmergeMe((*np));
		main.push_back(temp);
		if(pend.empty())
			free_lst(pend);
		free_lst(NP);
	}
	free_lst(sequence);
	return main;
}

void is_sorted(std::list<PmergeMe*>sequence)
{
	std::list<PmergeMe*>::iterator it = sequence.begin();
	std::list<PmergeMe*>::iterator itend = sequence.end();
	std::list<PmergeMe*>::iterator itsecond;
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
				return ;
			itsecond++;
		}
		it++;
	}
	std::cout << Y << "After:  ";
}

int check_fusion_sizes(std::list<PmergeMe*>sequence)
{
	std::list<PmergeMe*>::iterator it = sequence.begin();
	std::list<PmergeMe*>::iterator itsecond = sequence.begin();
	std::list<PmergeMe*>::iterator itend = sequence.end();
	while(it != itend)
	{
		itsecond++;
		if((*it)->size != (*itsecond)->size)
			return 0;
		it++, it++;
		itsecond++, itsecond++;
		if((*it)->size != (*itsecond)->size)
			return 0;
		return 1;
	}
	return 1;
}


int main(int argc, char **argv)
{
	if(argc == 1 || argv[1][0] == '\0')
		return (std::cerr << "Wrong number of arguments.\n"), 1;
	std::list<PmergeMe*>sequence;
	sequence = PmergeMe::init(argv);
	if(check_duplicate(sequence) || check_sintax(sequence, argv))
		return 1;
	size_t npairs = 1;
	size_t sqinitial = sequence.size();
	std::cout << B << "Before: "; print(sequence);
	std::clock_t start = std::clock();
	while((sqinitial / 2 ) > npairs)
	{
		sort(sequence, npairs);
		if(sequence.size() >= 4)
		{
			npairs = 2 * npairs;
			if(check_fusion_sizes(sequence))
				sequence = fusion(sequence, npairs);
		}
		else
			break ;
	}
	sort(sequence, npairs);
	while(npairs > 0)
	{
		label(sequence, npairs);
		sequence = jacobsthal(sequence, npairs);
		npairs = npairs / 2;
		if(npairs == 0)
		{
			is_sorted(sequence);
			std::clock_t end = std::clock();
			double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
			print(sequence);
			std::cout << Y <<"\nTime to process a range of " << sequence.size() << " elements with std::[..] : ";
			std::cout << time  << " us" << std::endl;
			free_lst(sequence);	
			return 0;
		}	
		if(npairs > 0) 
			sequence = divide(sequence, npairs);
	}
	free_lst(sequence);
	return 0;
}