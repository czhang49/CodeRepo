/**
 * @file dl_list.tcc
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <cassert>
#include <utility>
#include "dl_list.h"
#include <iostream>
#include <math.h>

namespace cs225
{

template <class T>
dl_list<T>::dl_list()
{
	head_=nullptr;
	tail_=nullptr;
	size_=0;
	
    /// @todo mp_list.1
}

template <class T>
dl_list<T>::dl_list(const dl_list& other)
{
	head_=nullptr;
	tail_=nullptr;
	size_=0;
	node* curr_=head_.get();
	for (uint64_t i=0;i<other.size();i++)
	{
		push_back(curr_->data);
		curr_=curr_->next.get();
    }
	/// @todo mp_list.1
    /// hint: re-use your push_X function(s)!
}

template <class T>
dl_list<T>::dl_list(dl_list&& other)
{
	size_=0;
	head_=nullptr;
	tail_=nullptr;
	swap(other);
    /// @todo mp_list.1
}

template <class T>
dl_list<T>& dl_list<T>::operator=(dl_list rhs)
{
    swap(rhs);
	return (*this);
	/// @todo mp_list.1
}

template <class T>
void dl_list<T>::swap(dl_list& other)
{
    std::swap(size_,other.size_);
	std::swap(tail_,other.tail_);
	head_.swap(other.head_);
	/// @todo mp_list.1
}

template <class T>
void dl_list<T>::push_back(T data)
{
	if (size_>0)
	{
		auto N=std::make_unique<node>(std::move(data));
	
		N->prev=tail_;
		tail_->next=std::move(N);
		tail_=tail_->next.get();
		size_++;	
	}
    /// @todo mp_list.1
    else
	{
		auto N=std::make_unique<node>(std::move(data));
	
		head_=std::move(N);
	
		tail_=head_.get();
	
		size_++;
	}
}

template <class T>
void dl_list<T>::push_front(T data)
{
	if (size_>0)
	{
		auto N=std::make_unique<node>(std::move(data));
	
		N->next=std::move(head_);
	
		head_=std::move(N);
	
		head_->next->prev=head_.get();
	
		++size_;
	}
	else 
	{	
		auto N=std::make_unique<node>(std::move(data));
		head_=std::move(N);
		tail_=head_.get();
		size_++;
	
	}
    /// @todo mp_list.1
}

template <class T>
void dl_list<T>::reverse()
{
    reverse(head_, tail_);
}

template <class T>
void dl_list<T>::reverse(std::unique_ptr<node>& first, node*& last)
{
	std::cout<<"Reverse "<<std::endl;
	if (first.get()==last)
	{	std::cout<<"if"<<std::endl;}
	else 
	{	

		std::cout<<"else"<<std::endl;
		node* End=last;			// get the end pointer
		node* Start=first.get();// get the start pointer
		node* OneBeforeStart=Start->prev;	// get one before start pointer		
		std::cout<<__LINE__<<std::endl;
		node* OneAfterEnd=End->next.get();	// to get one after the end
		
		int Cri1=(End->next.get()==nullptr);
		int Cri2=(Start->prev==nullptr);
		// This part intends to change all the previous ptr
		if(End->next.get()!=nullptr)
			End->next->prev=Start;	// make end next previous equal to start , if next is nullptr, no action
		
		End->prev=Start->prev;	// make end previous equal to start prev, if start has no previous, they are both nullptr. 
					

		node* curr=Start;		// make the current at the start place		
		for(;curr!=End;)		// current will stop at the end place
		{						// this is to change the previous
			curr->prev=curr->next.get();
			curr=curr->next.get();
		
		}
		std::cout<<__LINE__<<std::endl;	

		// the following intends to change all the next unique_ptr
		if((!Cri1) && (!Cri2))
		{	curr=OneAfterEnd;	// now the curr is at one after end PPP END
		
		std::cout<<__LINE__<<std::endl;	
			node* garbage;
			for(;curr!=OneBeforeStart;)	// PPP END
			{
				garbage=curr->prev->next.release();
				curr=curr->prev;	
			}
			
			curr=OneAfterEnd;
			for(;curr!=OneBeforeStart;)
			{
				curr->prev->next.reset(curr);
				curr=curr->prev;
			}
		// now curr points to one before the start place.
			last=Start;
		//	garbage=first.release();
		//	first.reset(End);	// the mystery of first first should be one of the next pointer, thus probably do not need to be changed value
		}
		if((Cri1) &&( !Cri2))
		{
			std::cout<<(Start->prev->next.get()==nullptr)<<std::endl;
			curr=Start;
			node* garbage;
			while (curr!=End)
			{
				garbage=curr->next.release();
				curr=curr->prev;
		
			}

		std::cout<<(Start->prev->next.get()==nullptr)<<std::endl;
			garbage=OneBeforeStart->next.release();
		
		//std::cout<<__LINE__<<std::endl;
			curr=Start;

			for (;curr!=OneBeforeStart;)
			{

				curr->prev->next.reset(curr);

				curr=curr->prev;

			}			
			last=Start;

			tail_=last;	
		}		
		if((!Cri1) && (Cri2))
		{
		std::cout<<__LINE__<<std::endl;	
			curr=OneAfterEnd;
			node* garbage;
			for(;curr!=End;)
			{
				garbage=curr->prev->next.release();
				curr=curr->prev;
			}
		std::cout<<__LINE__<<std::endl;	
			garbage=head_.release();
			curr=OneAfterEnd;
		std::cout<<__LINE__<<std::endl;	
			//int i=0;
			for(;curr!=End;)
			{//std::cout<<i<<std::endl;
			//	std::cout<<(End->next.get()==nullptr)<<std::endl;
				curr->prev->next.reset(curr);
				curr=curr->prev;
			}
		std::cout<<__LINE__<<std::endl;	
			head_.reset(End);
		std::cout<<__LINE__<<std::endl;	
			last=Start;
		}	
		if ((Cri1) && (Cri2))
		{
		std::cout<<__LINE__<<std::endl;	
			node* garbage;
			curr=Start;
			for(;curr!=End;)
			{
				garbage=curr->next.release();
				curr=curr->prev;
			}
			garbage=head_.release();
			curr=Start;
			for(;curr!=End;)
			{
				curr->prev->next.reset(curr);
				curr=curr->prev;
			}
			head_.reset(End);
			last=Start;
			tail_=last;
		}
	}
    /// @todo mp_list.1
}

template <class T>
void dl_list<T>::reverse_nth(unsigned n)
{	std::cout<<"Rever n "<<std::endl;
	node* countleft=head_.get();
	node* countright=countleft;
	node* temp=countleft;
	if (n>1 && size_>=2)	
	{
		for (uint64_t j=1;(j<n && countright->next.get()!=nullptr);j++)
			countright=countright->next.get();
		
		temp=countright->next.get();	
		reverse(head_,countright);
		countleft=temp;
		countright=countleft;
	
		
		for (uint64_t i=1;i<ceil((float)size()/n);i++)
		{
			uint64_t j=1;
			for (; (j<n && countright->next.get()!=nullptr);j++)
				countright=countright->next.get();
				
			temp=countright->next.get();
			std::cout<<(j==n)<<std::endl;
			std::cout<<(countright->next.get()==nullptr)<<std::endl;
			reverse(countleft->prev->next,countright);
			std::cout<<(countright->next.get()==nullptr)<<std::endl;
			countleft=temp;
			countright=countleft;	
			
		}
		//std::cout<<__LINE__<<std::endl;
		
		//std::cout<<__LINE__<<std::endl;
		//std::cout<<(temp==nullptr)<<std::endl;
	}
	
    /// @todo mp_list.1
}

template <class T>
void dl_list<T>::waterfall()
{
	if (size_>=3)
	{
		node* curr=head_.get();
		node* tobemoved;
		node* garbage;
		node* oneaftertobemoved;
		while (curr->next.get()!=tail_)
		{
			tobemoved=curr->next.get();
			oneaftertobemoved=tobemoved->next.get();	

			garbage=curr->next.release();
			garbage=tobemoved->next.release();

			oneaftertobemoved->prev=curr;
			tobemoved->prev=tail_;			
			
			curr->next.reset(oneaftertobemoved);
			tail_->next.reset(tobemoved);
			
			tail_=tobemoved;
			curr=curr->next.get();
		}
	}
    /// @todo mp_list.1
}

template <class T>
auto dl_list<T>::split(unsigned split_point) -> dl_list
{
    if (split_point >= size_)
        return {};

    if (split_point == 0)
    {
        dl_list lst;
        swap(*this);
        return lst;
    }

    auto old_size = size_;
    auto new_head = split(head_.get(), split_point);

    // set up current list
    size_ = split_point;
    for (tail_ = head_.get(); tail_->next; tail_ = tail_->next.get())
        ;

    // set up returned list
    dl_list ret;
    ret.head_ = std::move(new_head);
    for (ret.tail_ = ret.head_.get(); ret.tail_->next;
         ret.tail_ = ret.tail_->next.get())
        ;
    ret.size_ = old_size - split_point;
    return ret;
}

template <class T>
auto dl_list<T>::split(node* start, unsigned split_point)
    -> std::unique_ptr<node>
{
    assert(split_point > 0);
	node* curr=start;
	node* garbage;
	for (uint64_t i=0;(i<split_point && curr!=nullptr) ;i++)
	{
		curr=curr->next.get();
	}
	if (curr!=nullptr)
	{
		garbage=curr->prev->next.release();
		curr->prev=nullptr;
	}

	
	std::unique_ptr<node> newhead{curr};
	
	return newhead;
    /// @todo mp_list.2
}

template <class T>
void dl_list<T>::merge(dl_list& to_merge)
{
	//std::cout<<__LINE__<<std::endl;
    head_ = merge(std::move(head_), std::move(to_merge.head_));

	//std::cout<<__LINE__<<std::endl;
    for (tail_ = head_.get(); tail_->next; tail_ = tail_->next.get())
        ;
    size_ += to_merge.size_;
	//std::cout<<__LINE__<<std::endl;
    to_merge.tail_ = nullptr;
    to_merge.size_ = 0;
}

template <class T>
auto dl_list<T>::merge(std::unique_ptr<node> first,
                       std::unique_ptr<node> second) -> std::unique_ptr<node>

{
	node* garbage;
	if (second.get()==nullptr)
		return first;
	if (first.get()==nullptr)
	{
		garbage=second.release();
		first.reset(garbage);
		return first;
	}		
	//std::cout<<__LINE__<<std::endl;
    /// @todo mp_list.2
	node* curr1=first.get();
	node* curr2=second.get();
	//std::cout<<__LINE__<<std::endl;
	node* beginning=curr1;	// initilize beginning to be at curr1
	node* oneaftercurr1=curr1->next.get();
	node* oneaftercurr2=curr2->next.get();
	//node* garbage;
	//std::cout<<__LINE__<<std::endl;
	garbage=first.release();
	garbage=second.release();	

	//std::cout<<__LINE__<<std::endl;
	// This part deals with the initial case
	/*if (curr1->data <= curr->data)
	{
		beginning=curr1;
		garbage=curr1->next.release();
		garbage=curr2->next.release();
		
		curr1->next.reset(curr2);
		curr2->prev=curr1;
		if (oneaftercurr1!=nullptr)
		{
			oneaftercurr1->prev=curr2;
			curr2->next.reset(oneaftercurr1);
		}
		if (oneaftercurr2!=nullptr)
		{
			oneaftercurr2->prev=nullptr;
		}
		curr1=curr2;
		oneaftercurr1=curr1->next.get();
	}*/
	if (curr2->data < curr1->data) 
	{
		beginning=curr2;
		garbage=curr2->next.release();
		
		curr2->next.reset(curr1);
		curr1->prev=curr2;

		if (oneaftercurr2!=nullptr)
		{
			oneaftercurr2->prev=nullptr;
		}
		curr1=curr2;
		oneaftercurr1=curr1->next.get();
		curr2=oneaftercurr2;
		
	//std::cout<<__LINE__<<std::endl;
	}
	//std::cout<<__LINE__<<std::endl;
	// This part deals with the middle case
	while (curr2!=nullptr)
	{
		oneaftercurr2=curr2->next.get();
		
		if (oneaftercurr1==nullptr)
		{
			curr1->next.reset(curr2);
			curr2->prev=curr1;
			curr2=nullptr;
			oneaftercurr2=nullptr;	
		}
	//std::cout<<__LINE__<<std::endl;
		else if (curr2->data < oneaftercurr1->data)
			{	//std::cout<<"if"<<std::endl;
				garbage=curr1->next.release();
				garbage=curr2->next.release();
				
				curr1->next.reset(curr2);
				curr2->prev=curr1;
				if (oneaftercurr1!=nullptr)
				{
					curr2->next.reset(oneaftercurr1);
					oneaftercurr1->prev=curr2;
				}
				if (oneaftercurr2!=nullptr)
				{
					oneaftercurr2->prev=nullptr;
				}
				curr1=curr2;
				oneaftercurr1=curr1->next.get();
				curr2=oneaftercurr2;
			
			}	
			else
			{//std::cout<<" else"<<std::endl;
				curr1=oneaftercurr1;
				oneaftercurr1=curr1->next.get();
			}
		
	}
	//std::cout<<__LINE__<<std::endl;
	first.reset(beginning);
	/*if (oneaftercurr1==nullptr)
	{
		beginning=curr1;
		curr1->next.reset(curr2);
		curr2->prev==curr1;
	}
	else if (oneaftercurr1!=nullptr && oneaftercurr2!=nullptr)
	{
		if (curr1->data <= curr2->data)
		{
			beginning=curr1;
			garbage=curr1->next.release();
			garbage=curr2->next.release();
			curr1->next.reset(curr2);
			curr2->next.reset(oneaftercurr1);		
	
			curr2->prev=curr1;
			oneaftercurr1->prev=curr2;
			oneaftercurr2->prev=nullptr;

			curr2=oneaftercurr2;
			oneaftercurr2=curr2->next.get();
			curr1=curr1->next.get();		// because list1 is added node, so oneafter does not change
		}
		else
		{
			beginning=curr2;
			garbage=curr2->next.release();
			curr2->next.reset(curr1);
			
			curr1->prev=curr2;
			oneaftercurr2->prev=nullptr;

			oneaftercurr1=curr1;
			curr1=curr2;
			curr2=oneaftercurr2;
			oneaftercurr2=curr2->next.get();
		}
	
	// the following part deals with the middle case
		while (oneaftercurr1!=nullptr && oneaftercurr2!=nullptr)
		{
			if (curr1->data <= curr2->data)
			{
				garbage=curr1->next.release();
				garbage=curr2->next.release();
				curr1->next.reset(curr2);
				curr2->next.reset(oneaftercurr1);

				curr->prev=curr1;
				oneaftercurr1->prev=curr2;
				oneaftercurr2->prev=nullptr;

				curr2=oneaftercurr2;
				oneaftercurr2=curr2->next.get();
				curr1=curr1->next.get();
			}
			else
			{
				curr1=oneaftercurr1;
				oneaftercurr1=curr1->next.get();
			}
		}
	// the following part deals with the ending case
		if (oneaftercurr1==nullptr)
		{
			curr1->next.reset(curr2);
			curr2->prev=curr1;
		}	
		else
		{
		// while list1 has alo but list 2 has only one
		}
	
	}
	first.reset(beginning);*/
	//std::cout<<"merge finished"<<std::endl;
	return first;
}

template <class T>
void dl_list<T>::sort()
{
    if (!head_)
        return;

    head_ = mergesort(std::move(head_), size_);
    for (tail_ = head_.get(); tail_->next; tail_ = tail_->next.get())
        ;
}

template <class T>
auto dl_list<T>::mergesort(std::unique_ptr<node> start, uint64_t length)
    -> std::unique_ptr<node>
{
	std::unique_ptr<node> temp;
	std::unique_ptr<node> merge1;
	std::unique_ptr<node> merge2;
	node* rawpointer;
	if (length<=1 || start.get()==nullptr)
		return start;
	else 
	{
		rawpointer=start.get();
		temp=split(rawpointer,length/2);
		merge1=(mergesort(std::move(start),length/2));
		merge2=(mergesort(std::move(temp),(length-length/2)));
	
	}
	
	return merge(std::move(merge1),std::move(merge2));
    /// @todo mp_list.2
}

}
