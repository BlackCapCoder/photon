#ifndef UTIL_H
#define UTIL_H


// Check wether we are capable of super computation
namespace Super
{
  typedef void* (*funPtr) ();
  funPtr rec () { return (funPtr) rec; }
  funPtr next = (funPtr) rec;

  bool check ()
  {
    next = (funPtr) next ();
    return next == nullptr;
  }
};


// Some turing tarpit named I/D
// https://esolangs.org/wiki/I/D_machine
template <class I>
struct ID
{
  I   size;
  I * mem;
  I * ptr;

  ID (I size) : size {size}
  {
    ptr = mem = new I[size]();
  }

  ~ID () { delete mem; }


  // Process a single bit of input
  inline
  void step (const bool op)
  {
    if (op)
      ptr = mem + (*ptr % size);
    else
      ++*ptr;
  }

  // Arbitrary halting condition
  inline bool isHalt () const
  {
    return mem[0] == 2
        && mem[1] == 3
        && mem[2] == 5
        && mem[3] == 7
        && mem[4] == 11
        && mem[5] == 13
        && mem[6] == 17
        && mem[7] == 23
        && mem[8] == 27
        && mem[9] == 31
         ;
  }
};


#endif // ifndef UTIL_H
