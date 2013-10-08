#ifndef			FUNCTOR_HPP
#define			FUNCTOR_HPP

namespace	Tools
{

  template		<typename T>
  struct		Functor
  {

    template		<typename U>
    Functor(U t){}

    void		operator ()(){}

  };

  template		<typename T>
  struct		Functor<T ()>
  {
    struct		IType
    {
      virtual		~IType(){}
      virtual T		operator()() = 0;
    };

    template		<typename U>
    class		Type : public IType
    {

      U			type;

    public:

      Type (U type): type(type){}
      virtual		~Type(){}

      T			operator()(){ return (this->type)(); }

    };

  private:

    IType		*type;

  public:

    template		<typename U>
    Functor(U type) : type(new Type<U>(type)){}

    ~Functor(){ delete this->type; }

    T			operator()()
    {
      return (*this->type)();
    }

  };

  template		<typename T, typename V>
  struct		Functor<T (V)>
  {
    struct		IType
    {
      virtual		~IType(){}
      virtual T		operator()(V) = 0;
    };

    template		<typename U>
    class		Type : public IType
    {

      U			type;

    public:

      Type (U type): type(type){}
      virtual ~Type(){}

      T			operator()(V v1){ return (this->type)(v1); }

    };

  private:

    IType		*type;

  public:

    template		<typename U>
    Functor(U type) : type(new Type<U>(type)){}

    ~Functor(){ delete this->type; }

    T			operator()(V v1)
    {
      return (*this->type)(v1);
    }

  };

  template		<typename T, typename V, typename W>
  struct		Functor<T (V, W)>
  {
    struct		IType
    {
      virtual		~IType(){}
      virtual T		operator()(V, W) = 0;
    };

    template		<typename U>
    class		Type : public IType
    {

      U			type;

    public:

      Type (U type): type(type){}
      virtual ~Type(){}

      T			operator()(V v1, W v2){ return (this->type)(v1, v2); }

    };

  private:

    IType		*type;

  public:

    template		<typename U>
    Functor(U type) : type(new Type<U>(type)){}

    ~Functor(){ delete this->type; }

    T			operator()(V v1, W v2)
    {
      return (*this->type)(v1, v2);
    }

  };


  template		<typename T, typename V, typename W, typename X>
  struct		Functor<T (V, W, X)>
  {
    struct		IType
    {
      virtual		~IType(){}
      virtual T		operator()(V, W, X) = 0;
    };

    template		<typename U>
    class		Type : public IType
    {
      U			type;

    public:

      Type (U type): type(type){}
      virtual ~Type(){}

      T			operator()(V v1, W v2, X v3)
      {
	return (this->type)(v1, v2, v3);
      }

    };

  private:

    IType		*type;

  public:

    template <typename U>Functor(U type) : type(new Type<U>(type)){}
    ~Functor(){ delete this->type; }

    T			operator()(V v1, W v2, X v3)
    {
      return (*this->type)(v1, v2, v3);
    }

  };

};

#endif
