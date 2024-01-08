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
	* @brief Перегрузка оператора равно
	* @param rha Первый аргумент для сравнения
	* @param lha Второй аргумент для сравнения
	* @return false если равны и true если н ет
	*/
	template<typename T>
	bool operator==(const List<T>& rha, const List<T>& lha) noexcept;
	
	/**
	* @brief Перегрузка оператора не равно
	* @param rha Первый аргумент для сравнения
	* @param lha Второй аргумент для сравнения
	* @return true если равны и false если нет
	*/
	template<typename T>
	bool operator!=(const List<T>& rha, const List<T>& lha) noexcept;
	
	/**
	* @brief Перегрузка оператора вывода
	* @return Поток вывода со списком
	*/
	template<typename T>
	std::ostream& operator<<(std::ostream& os, List<T>& list) noexcept;
	
	

	template<typename T>
	class List final
	{
	private:
		Node<T>* head;
		Node<T>* tail;
		size_t size;

		/**
		* @brief Перемещает поля двух обектов
		* @param list Список для перемещения
		*/
		void swap(List& list);

	public:

		/**
		* @brief Создает объект типа List
		*/
		List();

		/**
		* @brief Создает объект типа List по initializer_list'у
		* @param list Список по которому будет создаваться список
		*/
		List(std::initializer_list<T> list);

		/**
		* @brief Чистит память за объектом типа List
		*/
		~List();

		/**
		* @brief Перегрузка оператора копирования
		* @param list Список для копирования
		* @return Список скопированный с list
		*/
		List<T>& operator=(const List<T>& list);

		/**
		* @brief Перегрузка оператора перемещения
		* @param list Список для мува
		* @return Список после мува
		*/
		List<T>& operator=(List<T>&& list) noexcept;

		/**
		* @brief Перегрузка конструктора копирования
		* @param list Список для копирования
		*/
		List(const List<T>& list);

		/**
		* @brief Перегрузка конструктора перемещения
		* @param list Список для мува
		*/
		List(List<T>&& list) noexcept;

		/**
		* @brief Удаление всех элементов списка
		*/
		void clear();

		/**
		* @brief Добавление элемента в начало списка
		* @param value Элемент для добавления
		*/
		void push_forward(const T& value);

		/**
		* @brief Добавление элемента в конец списка
		* @param value Элемент для добавления
		*/
		void push_back(const T& value);

		/**
		* @brief Удаление элемента с начала списка
		*/
		void pop_forward();

		/**
		* @brief Есть ли элементы в списке
		* @return true - если список не пустой и false если он пустой
		*/
		bool has_elements() const;

		/**
		* @brief Превращение списка в строку
		* @return Строка по списку
		*/
		std::string to_string() const;

		/**
		* @brief Получение элемента с 'индексом' в списке
		* @param index Номер элемента в списке относительно начала
		* @return Значение элемент списка
		*/
		T get(size_t index) const;
		
	};

	template<typename T>
	class Node
	{
	public:
		/**
		* @brief Создает объект типа Node
		* @param value Значение ноды
		* @param next_node Следующая нода
		*/
		Node(T value, Node<T>* next_node = nullptr);
		T value;
		Node<T>* next_node;
	};

	template<typename T>
	inline Node<T>::Node(T value, Node<T>* next_node)
		:value(value), next_node(next_node)
	{
	}

	template<typename T>
	inline void List<T>::swap(List& list)
	{
		std::swap(this->head, list.head);
		std::swap(this->tail, list.tail);
		std::exchange(this->size, list.size);
	}

	template<typename T>
	inline List<T>::List()
		:head(nullptr), tail(nullptr), size(0)
	{
	}

	template<typename T>
	inline List<T>::List(std::initializer_list<T> list)
		: List()
	{
		for (auto& value : list)
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
			this->swap(temp);
		}
		return *this;
	}

	template<typename T>
	inline List<T>& List<T>::operator=(List<T>&& list) noexcept
	{
		if (*this != list) 
		{
			this->swap(list);
		}
		return *this;
	}

	template<typename T>
	inline List<T>::List(const List<T>& list)
		:List()
	{
		List temp{};
		Node<T>* curr = list.head;
		while (curr != nullptr)
		{
			temp.push_back(curr->value);
			curr = curr->next_node;
		}
		this->swap(temp);
	}

	template<typename T>
	inline List<T>::List(List<T>&& list) noexcept
		:List()
	{
		this->swap(list);
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
	inline void List<T>::push_forward(const T& value)
	{
		Node<T>* next_head = new Node<T>(value, this->head);
		this->head = next_head;
		if (!this->has_elements())
		{
			this->tail = next_head;
		}
		this->size++;
	}
	template<typename T>
	inline void List<T>::push_back(const T& value)
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
		this->size++;
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
		this->size--;
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
	inline T List<T>::get(size_t index) const
	{
		if (this->is_empty() || (index + 1) > this->size)
		{
			throw std::out_of_range("Wrong Index");
		}
		Node<T>* temp = this->head;
		for (size_t i = 0; i < index; i++)
		{
			temp = temp->next;
		}
		return temp->value;
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