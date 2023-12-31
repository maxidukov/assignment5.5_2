#include <iostream>
#include <stdexcept>


template <class T>
class table{
   int size_[2];
   T** ppT_;
   public:
   table(int a, int b): ppT_(new T*[a]){
     size_[0] = a;
     size_[1] = b;
     for(int i{};i<a;i++){
       ppT_[i] = new T[b];
     }
   }
   int Size() const{return size_[0]*size_[1];}
   int Size(int i) const{
     if(i==0 || i==1){return size_[i];}
     else{throw std::out_of_range("Dimension index out of range");} //JUST IN CASE...
   }
   //int (&Dims())[2] const{return dims_;} //NICE TRY...https://stackoverflow.com/questions/3473438/return-array-in-a-function
   const T* operator[](int i) const{return ppT_[i];}
   T* operator[](int i){return ppT_[i];}

   table(const table& table_first): ppT_(new T*[table_first.size_[0]]) {
      size_[0] = table_first.size_[0];
      size_[1] = table_first.size_[1];
      for (int i = 0; i < size_[0]; ++i) {
        ppT_[i] = new T[size_[1]];
        for(int j = 0; j < size_[1]; ++j) {
          ppT_[i][j] = table_first.ppT_[i][j];
        }
      }
   }
   table& operator=(const table &table_first) { // deep copy assignment overloading
      // self-assignment is a special case: don't need to do anything
      if (this != &table_first) {
        for(int i{};i<size_[0];i++){
           delete [] ppT_[i];
         }
         delete [] ppT_;
        size_[0] = table_first.size_[0];
        size_[1] = table_first.size_[1];
        ppT_ = new T*[size_[0]];
        for (int i = 0; i < size_[0]; ++i) {
          ppT_[i] = new T[size_[1]];
          for(int j = 0; j < size_[1]; ++j) {
            ppT_[i][j] = static_cast<T>(table_first.ppT_[i][j]);
          }
        }
      }
      return *this;
    }
    template<class U>
    //table<T>& operator=(const table<U> &table_first) =delete;
    table& operator=(const table<U> &table_first) { // deep copy assignment overloading
       // self-assignment is a special case: don't need to do anything
       //if (this != &table_first) {
         for(int i{};i<size_[0];i++){
            delete [] ppT_[i];
          }
          delete [] ppT_;
         size_[0] = table_first.Size(0);
         size_[1] = table_first.Size(1);
         ppT_ = new T*[size_[0]];
         for (int i = 0; i < size_[0]; ++i) {
           ppT_[i] = new T[size_[1]];
           for(int j = 0; j < size_[1]; ++j) {
             ppT_[i][j] = static_cast<T>(table_first[i][j]);
           }
         }
       //}
       return *this;
     }
   ~table(){
     for(int i{};i<size_[0];i++){
       delete [] ppT_[i];
     }
     delete [] ppT_;
   }
};

int main() {
  auto test = table<int>(2, 3);
  test[0][0] = 4;
  std::cout << test[0][0]; // выводит 4
  std::cout << std::endl;
  auto test2(test);
  std::cout << test2[0][0] << std::endl; // выводит 4

  //TESTING OVERLOADED ASSIGNMENT OPERATOR
  //BOTH TABLES INTEGER TYPE
  auto test3 = table<int>(3, 4);
  test3 = test;
  std::cout << test3[0][0] << std::endl; // выводит 4

  //DIFFERENT TYPES
  auto test4 = table<double>(3, 4);
  test4 = test;
  std::cout << test4[0][0] << std::endl; // выводит 4
}
