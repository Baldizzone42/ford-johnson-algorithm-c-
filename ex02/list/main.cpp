/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:06:32 by jormoral          #+#    #+#             */
/*   Updated: 2025/05/06 16:51:52 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


bool digit(char c)
{
	if(c >= '0' && c <= '9')
		return true;
	return false;
}

int check_sintax(std::list<PmergeMe*>lst, char **argv)
{
	if(lst.size() == 0 || lst.size() > 3000)
		return (std::cout <<"Non-orderable number size.\n"), 1;
		
	size_t i = 	1;
	while(argv[i])
	{
		int j = 0;
		while(argv[i][j])
		{
			if(digit(argv[i][j]) == false)
				return (std::cout << "Error: Non-numeric character found"), 1;
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
				return (std::cout << "Error: repeated number\n"), 1;
			itsecond++;
		}
		it++;
	}
	return 0;
}


void free_lst(std::list<PmergeMe*>lst)
{
	std::list<PmergeMe*>::iterator it = lst.begin();
	std::list<PmergeMe*>::iterator itend = lst.end();
	while(it != itend)
	{
		//delete [](*it)->array;
		delete ((*it));
		it = lst.erase(it);
	}
	lst.clear();
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
			std::cout << (*it)->array[i] << ".";
			i++;
		}
		//std::cout << VERDE << (*it)->label << " ";
		std::cout << " // ";
		it++;
	}
	std::cout << std::endl << std::endl;
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
			//std::cout << ROJO << npairs << std::endl;
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
/* 	std::list<PmergeMe*>::iterator itt = sequence.begin();
	std::list<PmergeMe*>::iterator ittend = sequence.end();
	while(itt != ittend)
	{
		std::cout << (*itt)->label << std::endl;
		itt++;
	} */
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
	
	//int i = 1;
	/* std::cout << VERDE << "ANTES: " << std::endl;
	print(sequence); */
	while(it != itend)
	{
		//std::cout << i++ << std::endl;
		if((*it)->size > (int)npairs)
		{
			PmergeMe **temp;
			//std::cout <<  ROJO << (*it)->array << std::endl;
			temp = divide_node((*it), npairs);
			//std::cout << MORADO << temp[0]->array[0] << " " << temp[1]->array[0] << std::endl;
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
	/* std::cout << VERDE << "DESPUES: " << std::endl;
	print(result); */
	return result;
}

std::list<PmergeMe*> final_jacob(std::list<PmergeMe*> main, std::list<PmergeMe*> pend , size_t npairs)
{

	while(pend.size() > 0)
	{	
		std::list<PmergeMe*>::iterator rev = pend.end();
		//std::cout << VERDE; print(pend);
		rev--;
		//std::cout << MORADO <<(*rev)->array[0] << std::endl;
		//std::cout << "hola" << std::endl;
		//std::cout << AMARILLO; print(main);
		std::list<PmergeMe*>::iterator it = main.begin();
		std::list<PmergeMe*>::iterator itend = main.end();
		while(it != itend)
		{
			//std::cout << "Npairs ----------------> " << npairs << std::endl;
			if((*it)->array[npairs - 1] > (*rev)->array[npairs - 1])
			{
			//	std::cout << "ruina" << std::endl;
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
				//pend.erase(rev);
				//free_lst(pend);
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
		std::cout << ROJO << "jacbobsss level" << std::endl;
		while(out != outend)
		{ 
			//std::cout << (*out)->lbl << "-" <<x << std::endl; 
			if((*out)->lbl == x)
			{
				//std::cout <<  "encontro b3 :))))))))))))))))))))))))))" << std::endl;
				get_out = 1;
			}
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
				//std::cout << (*pet)->lbl << std::endl;
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
	
	//// Añadimos los nodos que corresponde tanto a Main, Pend & Non-participating
	//std::cout << "SIZE SEQUENCE: " << sequence.size() << std::endl;
	//print(sequence);
	while(it != itend && (*it)->size == (int)npairs)
	{
		if((*it)->label == "b1" || (*it)->label[0] == 'a')
		{
			PmergeMe *temp = new PmergeMe((*it));
			main.push_back(temp);
			//delete (*it);
			//it = sequence.erase(it);
		}
		else if((*it)->label[0] == 'b')
		{
			PmergeMe *temp = new PmergeMe((*it));
			pend.push_back(temp);
			//delete (*it);
			//it = sequence.erase(it);
		}
		it++;
	}
	/* std::cout << VERDE << "pastora: " << std::endl;
	print(sequence);
	std::cout << AMARILLO << "Main: " << main.size() << std::endl;
	print(main);
	std::cout << AMARILLO << "Pend: " << pend.size() << std::endl;
	print(pend); */
	if(it != itend)
	{
		PmergeMe *temp = new PmergeMe((*it));
		NP.push_back(temp);
	}
	std::cout << AMARILLO  << "NP: "<< NP.size() << std::endl; /* 
	std::cout << AMARILLO << "Main: " << main.size() << std::endl;
	std::cout << AMARILLO << "Pend: " << pend.size() << std::endl;
	std::cout << AMARILLO  << "NP: "<< NP.size() << std::endl; */
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
	print(main);
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
	//size_t level = 1;
	std::cout << AZUL << "Our original sequence: \n";
	print(sequence);
	size_t sqinitial = sequence.size();
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
		/* std::cout << "ANTES: " << std::endl;
		print(sequence); */
		label(sequence, npairs);
		sequence = jacobsthal(sequence, npairs);
		
		npairs = npairs / 2;
		if(npairs == 0)
		{
			std::cout << VERDE << sequence.size() << std::endl;
			is_sorted(sequence);
			print(sequence);
			free_lst(sequence);	
			return 0;
		}	
		if(npairs > 0)
			sequence = divide(sequence, npairs);
		//std::cout << AMARILLO << "Divide: " << std::endl, print(sequence);
		//std::cout << MORADO << "SECUENCE SORT! " << std::endl, print(sequence);
		//std::cout << MORADO << "Pend: ", print(pend);
		//std::cout << MORADO << "Non-P: ", print(NP);
		//std::cout << "-------------------------" << std::endl;
	}
	std::cout << sequence.size() << std::endl;
	free_lst(sequence);
	return 0;
}