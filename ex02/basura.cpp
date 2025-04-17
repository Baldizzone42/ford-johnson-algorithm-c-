/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basura.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:52:14 by jormoral          #+#    #+#             */
/*   Updated: 2025/04/17 09:58:42 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 /* #include "PmergeMe.hpp"

size_t size_iterator(std::list<int *>::iterator *it)
{
	size_t cn = 0;
	std::list<int*>::iterator itemp = *it;
	while(*(*itemp))
	{
		cn++;
		
		//std::cout <<*(*itemp) <<  " " << cn << std::endl;
		(*itemp)++;
	}
	//std::cout << " ]" << std::endl;
	int tn = cn;
	while(tn > 0)
	{
		(*itemp)--;
		tn--;
	}
	return cn;
}



void print_sort(PmergeMe *merge, int npairs)
{
		std::list<int*>::iterator it = merge->Og.begin();
		std::list<int*>::iterator itsecond = merge->Og.begin();
		std::list<int*>::iterator e = merge->Og.end();
		itsecond++;
		//(void)npairs;
		while(it != e)
		{
			int i = 0;
			std::cout << "[ ";
			while(i < npairs)	
			{
				std::cout << (*it)[i] << " ";
				i++;
			}
			it++;
			itsecond++;
			std::cout << "]";
		}
		 if(n >= (merge->Og.size())  && n % 2 != 0)
				print_sort(merge + n, 1);
		else 
			std::cout << std::endl;
}

int* fusion_array(int *a, int *b, size_t npairs)
{
	int *temp = new int[npairs * 2];
	size_t i = 0;
	size_t j = 0;
	while(i < npairs)
	{
		temp[j] = a[i];
		i++;
		j++;
	}
	i = 0;
	while(i < npairs)
	{
		temp[j] = b[i];
		i++;
		j++;
	}
	return temp;
}

int* infusion_array(int *a, size_t size)
{
	int *temp = new int[size];
	std::cout << "INFUSION Size: "  << size << std::endl;
	
	size_t i = 0;
	size_t j = 0;
	while(i < size)
	{
		temp[j] = a[i];
		i++;
		j++;
	}
	std::cout <<  "sizeof: " << sizeof(temp) <<std::endl;
	return temp;
}



PmergeMe* fusion_list(PmergeMe *merge, size_t npairs)
{
	PmergeMe *result = new PmergeMe;
	std::list<int*>::iterator it = merge->Og.begin();
	std::list<int *>::iterator itsecond =merge->Og.begin();
	std::list<int*>::iterator itend = merge->Og.end();
	std::list<int*>tactico;
	itsecond++;
	while(it != itend)
	{
		if(itsecond != itend)
		{
			int *temp = new int[npairs];
			temp = fusion_array((*it), (*itsecond), npairs);
			tactico.push_back(temp);
			it++;
			itsecond++;
			//std::cout << "a" << std::endl;
		}
		if(itsecond == itend && merge->Og.size() % 2 != 0)
		{ 
				int *test = infusion_array((*it), size_iterator(&it));
				//size_t i = 0;
				 while(i < size_iterator(&it)){
					std::cout << test[i] << std::endl;
					i++;} 
				//std::cout << "Poronga : " << size_iterator(&it) << std::endl;
				tactico.push_back(test);
 				merge->Og.clear();
				result->Og = tactico;
				print_sort(result, size_iterator(&it));
				std::cout << "b" << std::endl; 
				//break;
		}
		else if(itsecond == itend)
			break;
		it++;
		itsecond++;
	}
	merge->Og.clear();
	result->Og = tactico;

	
	return result;
}

 bool max_n(std::list<int*>::iterator it, std::list<int *>::iterator itsecond)
{
	int itmax = 0;
	int itsecondmax = 0;
	int i = 0;
	int j = 0;
	while((*it)[i])
	{
		if(itmax < (*it)[i])
			itmax = (*it)[i];
		i++;
	}
	while((*itsecond)[j])
	{
		if(itsecondmax < (*itsecond)[j])
			itsecondmax = (*itsecond)[j];
		j++;
	}
	if(itmax > itsecondmax && i == j)
			return true;
	return false;
} 


void sort(PmergeMe *merge, size_t npairs)
{ 	
	//max_n(it, itsecond)
	std::list<int*>::iterator it = merge->Og.begin();
	std::list<int*>::iterator itsecond = merge->Og.begin();
	std::list<int*>::iterator itend = merge->Og.end();
	while(itsecond != itend)
	{
		itsecond++;
		if(itsecond != itend && (*it)[npairs - 1] > (*itsecond)[npairs - 1])
		{
			int *temp = (*it);
			(*it) = (*itsecond);
			(*itsecond) = temp;
		}
		else if(itsecond == itend)
			break;
		it++,it++;
		itsecond++;
	}
}



int main(int argc, char **argv)
{
	std::list<std::string>split;
	PmergeMe *merge = new PmergeMe();
	if(argc == 1)
		return 1;
	int i = 1;
	while(argv[i])
	{
		std::string arg = argv[i];
		int *temp = new int[1];
		temp[0] = atoi(arg.c_str());
		merge->Og.push_back(temp);
		i++;
	}
	size_t size_merge = merge->Og.size();
	merge->sizeog = merge->Og.size();
	size_t npairs = 1;
	int level = 0;
	while(size_merge >= npairs)
	{
		level++;
		std::cout << "Sequence after sorting " << level << std::endl;
		sort(merge, npairs);
		print_sort(merge, npairs);
		merge = fusion_list(merge, npairs);
		npairs = npairs * 2;
		std::cout << "Fusion " << level << std::endl;
		print_sort(merge, npairs);
		size_merge = merge->Og.size();
		 std::cout <<"Tamaño total merge: " << size_merge << std::endl;
		std::cout << "Npairs: " << npairs << std::endl; 
	}
	return 0;
	
} */
 