#pragma once
#include <iostream>
#include <sstream>

namespace miit::list
{
	template<typename T>
	class Node;

	template<typename T> 
	class List;
	/**
	* @brief ���������� ��������� �����
	* @param rha ������ �������� ��� ���������
	* @param lha ������ �������� ��� ���������
	* @return false ���� ����� � true ���� � ��
	*/
	template<typename T>
	bool operator==(const List<T>& rha, const List<T>& lha) noexcept;
	
	/**
	* @brief ���������� ��������� �� �����
	* @param rha ������ �������� ��� ���������
	* @param lha ������ �������� ��� ���������
	* @return true ���� ����� � false ���� ���
	*/
	template<typename T>
	bool operator!=(const List<T>& rha, const List<T>& lha) noexcept;
	
	/**
	* @brief ���������� ��������� ������
	* @return ����� ������ �� �������
	*/
	template<typename T>
	std::ostream& operator<<(std::ostream& os, List<T>& list) noexcept;
	
	

	template<typename T>
	class List final
	{
	private:
		Node<T>* head;
		Node<T>* tail;

	public:

		/**
		* @brief ������� ������ ���� List
		*/
		List();

		/**
		* @brief ������� ������ ���� List �� initializer_list'�
		* @param list ������ �� �������� ����� ����������� ������
		*/
		List(std::initializer_list<T> list);

		/**
		* @brief ������ ������ �� �������� ���� List
		*/
		~List();


		/**
		* @brief ���������� ��������� �����������
		* @param list ������ ��� �����������
		* @return ������ ������������� � list
		*/
		List<T>& operator=(const List<T>& list);

		/**
		* @brief ���������� ��������� �����������
		* @param list ������ ��� ����
		* @return ������ ����� ����
		*/
		List<T>& operator=(List<T>&& list) noexcept;

		/**
		* @brief ���������� ������������ �����������
		* @param list ������ ��� �����������
		*/
		List(const List<T>& list);

		/**
		* @brief ���������� ������������ �����������
		* @param list ������ ��� ����
		*/
		List(List<T>&& list) noexcept;


		/**
		* @brief �������� ���� ��������� ������
		*/
		void clear();

		/**
		* @brief ���������� �������� � ������ ������
		* @param value ������� ��� ����������
		*/
		void push_forward(T value);

		/**
		* @brief ���������� �������� � ����� ������
		* @param value ������� ��� ����������
		*/
		void push_back(T value);

		/**
		* @brief �������� �������� � ������ ������
		*/
		void pop_forward();

		/**
		* @brief ���� �� �������� � ������
		* @return true - ���� ������ �� ������ � false ���� �� ������
		*/
		bool has_elements() const;

		/**
		* @brief ����������� ������ � ������
		* @return ������ �� ������
		*/
		std::string to_string() const;

		
	};

	template<typename T>
	class Node
	{
	public:
		/**
		* @brief ������� ������ ���� Node
		* @param value �������� ����
		* @param next_node ��������� ����
		*/
		Node(T value, Node<T>* next_node);
		T value;
		Node<T>* next_node;
	};

	template<typename T>
	inline Node<T>::Node(T value, Node<T>* next_node)
		:value(value), next_node(next_node)
	{
	}

	template<typename T>
	inline List<T>::List()
		:head(nullptr), tail(nullptr)
	{
	}

	template<typename T>
	inline List<T>::List(std::initializer_list<T> list)
		: head(nullptr), tail(nullptr)
	{
		for (auto value : list)
		{
			this->push_back(value);
		}
	}

	template<typename T>
	inline List<T>::~List()
	{
		this->clear();
	}

	template<typename T>
	inline List<T>& List<T>::operator=(const List<T>& list)
	{
		if (*this != list) 
		{
			List temp{ list };
			std::swap(temp.head, this->head);
			std::swap(temp.tail, this->tail);
		}
		return *this;
	}

	template<typename T>
	inline List<T>& List<T>::operator=(List<T>&& list) noexcept
	{
		if (*this != list) 
		{
			*this = std::move(list);
		}
		return *this;
	}

	template<typename T>
	inline List<T>::List(const List<T>& list)
		:head(nullptr), tail(nullptr)
	{
		List temp{};
		Node<T>* curr = list.head;
		while (curr != nullptr)
		{
			temp.push_back(curr->value);
			curr = curr->next_node;
		}
		std::swap(temp.head, this->head);
		std::swap(temp.tail, this->tail);
	}

	template<typename T>
	inline List<T>::List(List<T>&& list) noexcept
		:head(nullptr), tail(nullptr)
	{
		*this = std::move(list);
	}

	template<typename T>
	inline void List<T>::clear()
	{
		while (this->has_elements())
		{
			this->pop_forward();
		}
	}
	template<typename T>
	inline void List<T>::push_forward(T value)
	{
		Node<T>* next_head = new Node<T>(value, this->head);
		this->head = next_head;
		if (!this->has_elements())
		{
			this->tail = next_head;
		}
	}
	template<typename T>
	inline void List<T>::push_back(T value)
	{
		Node<T>* next_tail = new Node<T>(value, nullptr);
		if (this->has_elements())
		{
			this->tail->next_node = next_tail;
			this->tail = next_tail;
		}
		else
		{
			this->tail = next_tail;
			this->head = next_tail;
		}
	}

	template<typename T>
	inline void List<T>::pop_forward()
	{
		if (!this->has_elements())
		{
			throw std::out_of_range("List is Empty");
		}
		Node<T>* next_head = this->head->next_node;
		delete this->head;
		this->head = next_head;
	}

	template<typename T>
	inline bool List<T>::has_elements() const
	{
		return this->head != nullptr;
	}

	template<typename T>
	inline std::string List<T>::to_string() const
	{
		std::stringstream buffer;
		Node<T>* curr = this->head;
		while (curr != nullptr)
		{
			buffer << curr->value;
			buffer << " ";
			curr = curr->next_node;
		}
		return buffer.str();
	}

	template<typename T>
	bool operator==(const List<T>& rha, const List<T>& lha) noexcept
	{
		return (rha.to_string() == lha.to_string());
	}

	template<typename T>
	bool operator!=(const List<T>& rha, const List<T>& lha) noexcept
	{
		return !(rha == lha);
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, List<T>& list) noexcept
	{
		return os << list.to_string();
	}
}