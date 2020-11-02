/* Define all your MyVector-related functions here.
 * Also, define the swap function here.
 * You do not need to include the h file.
 * It included this file at the bottom.
 */

//sets my_id to MST username
void get_identity(string &my_id)
{
  my_id = "hdpg4c";
}

template <typename T>
void MySwap(T &a, T &b)
{
  //swaps two numbers
  T c = a; //variable of type T
  a = b; //a is equal to b
  b = c; //b is eqaul to c
}

template <typename T>
MyVector<T>::MyVector()
{
  //default array to nullptr
  m_data = nullptr;
  reserved_size = 0; //defaults the reserved_size to 0
  data_size = 0; //defaults the data size to 0
}

//deep copy
template <typename T>
MyVector<T> & MyVector<T>::operator=(const MyVector<T> &source)
{
  reserved_size = source.reserved_size; //sets reserved_size to source reserved_size
  data_size = source.data_size; //sets data_size to source data_size
  m_data = new T[reserved_size]; //new pointer

  for(int i = 0; i < reserved_size; i++)
  {
    m_data[i] = source.m_data[i]; //iterates for each reserved_size and
                                  //sets data arrray to source data
  }

  return *this;
}

//deep copy
template <typename T>
MyVector<T>::MyVector(const MyVector<T> &source)
{
  reserved_size = source.reserved_size; //sets the source capacity to reserved_size
  data_size = source.data_size; //sets the data_size to source size
  m_data = new T[reserved_size];

  for(int i = 0; i < reserved_size; i++)
    m_data[i] = source.m_data[i];
}

//returns the element of array by using reference
template <typename T>
T & MyVector<T>::operator[](int i)
{
  return m_data[i];
}

//Returns the element stored at the index by reference and
//throw an std::out_of_range exception when out-of-bounds
template <typename T>
T & MyVector<T>::at(int index)
{
  if(index < 0 ||index > (reserved_size - 1)) //checks if index is less than 0
  {                                           //checks if the out of bound of array
    throw std::out_of_range("out-of-bounds");
  }
  return m_data[index]; //returns m_data[index]
}

//Funciton returns the element stored at the front of the vector
template <typename T>
T & MyVector<T>::front()
{
  return m_data[0]; //front of vector
}

//Function returns the element stored at the back of the vector
template <typename T>
T & MyVector<T>::back()
{
  return m_data[data_size - 1]; //back of vecor
}

//Function returns the maximum numner of elements that can be stored
//in current vector
template <typename T>
int MyVector<T>::capacity()
{
  return reserved_size;
}

//Function
template <typename T>
void MyVector<T>::reserve(int new_cap)
{
  //Increases max_size to new_cap if new_cap > max_size
  if(new_cap > reserved_size)
  {
    T *data = m_data; //new pointer of type T
    m_data = new T[new_cap];
    for(int i = 0; i < data_size; i++)
    {
      if(data != nullptr) //checks if data is not equal to nullptr
        m_data[i] = data[i]; //if yes, then sets m_data[i] to pointer data[i]
    }
    delete[] data; //deletes the array/memory
    reserved_size = new_cap; //sets reserved size to new_cap value
  }
}

//Function should shrink such that the array is 2x as big as the data.
template <typename T>
void MyVector<T>::shrink_to_fit()
{
  int new_dataSize = data_size * 2; //data_size is increased times 2
  T *array = new T[new_dataSize]; //new pointer array

  for(int i = 0; i < data_size; i++) //iterates through each data_size
  {
    array[i] = m_data[i];
  }
  reserved_size = new_dataSize; //reserved_size equal to new data size value
  delete[] m_data; //deletes the array
  m_data = array; //sets m_data to pointer array
}

//Funciton fill up the array with count of T value
template <typename T>
void MyVector<T>::assign(int count, const T &value)
{
  //replaces new current array
  m_data = new T[count];

  for(int i = 0; i < count; i++)
    m_data[i] = value;

  data_size = count; //data_size is set to count
  reserved_size = count; //reserved_size is set to count
}

//Function clears the MyVector
template <typename T>
void MyVector<T>::clear()
{
  //current size and storage is set back to 0
  data_size = 0;
  reserved_size = 0;

  delete[] m_data; //deallocate the elements in m_data array
  m_data = nullptr; //m_data is set to null pointer
}

//funciton to appends the value x to the end of an MyVector
template <typename T>
void MyVector<T>::push_back(const T &x)
{
  data_size++; //current size incremented by 1
  if(data_size >= reserved_size) //if max size is reached
    reserve(data_size * 2); //storage array is grown

  m_data[data_size - 1] = x;
}

//Funciton removes the last element of the vector
template <typename T>
void MyVector<T>::pop_back()
{
  if(data_size > 0) //if data size is more than 0
  {
    data_size--; //current size is decremented by 1

    if(reserved_size > (data_size*4))
      shrink_to_fit(); //calls the shrink_to_fit function
  }
}

//Function inserts the value of x at the position i in the MyVector array
template <typename T>
void MyVector<T>::insert(int i, const T &x)
{
  data_size++; //current size incremented by 1

  if(data_size >= reserved_size) //if max size reached
    reserve(reserved_size*2); //storage is grown

  for(int j = data_size; j > i; j--)
    m_data[j] = m_data[j-1];

  m_data[i] = x; //i as reference is set to x
}

//Function removes the elements at index i in the array
template <typename T>
void MyVector<T>::erase(int i)
{
  if(i < reserved_size)
  {
    if(data_size > 0) //if the size of the list is greater than 0
      data_size--; //current size is decremented by 1

    for(int i; i < end(); i++)
      m_data[i] = m_data[i+1];

    if(reserved_size > (data_size*4)) //if the size less than 1/4 max size
      shrink_to_fit(); //storage array is shrunk
  }
}

//Function returns the size of the actual data stored in the array list
template <typename T>
int MyVector<T>::size()
{
  return data_size;
}

//Function to delete the array
template <typename T>
MyVector<T>::~MyVector()
{
  delete[] m_data;
}
