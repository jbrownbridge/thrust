/*
 *  Copyright 2008-2009 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


/*! \file replace.inl
 *  \brief Inline file for replace.h.
 */

#include <komrade/replace.h>
#include <komrade/transform.h>
#include <komrade/iterator/iterator_traits.h>

namespace komrade
{

namespace detail
{

// this functor receives x, and returns a new_value if predicate(x) is true; otherwise,
// it returns x
template<typename Predicate, typename NewType, typename InputType, typename OutputType>
  struct new_value_if
{
  new_value_if(Predicate p, NewType nv):pred(p),new_value(nv){}

  __host__ __device__ OutputType operator()(const InputType &x) const
  {
    return pred(x) ? new_value : x;
  } // end operator()()
  
  Predicate pred;
  NewType new_value;
}; // end new_value_if

}; // end detail  

template<typename InputIterator, typename OutputIterator, typename Predicate, typename T>
  OutputIterator replace_copy_if(InputIterator first, InputIterator last,
                                 OutputIterator result,
                                 Predicate pred,
                                 const T &new_value)
{
  typedef typename komrade::iterator_traits<InputIterator>::value_type InputType;
  typedef typename komrade::iterator_traits<OutputIterator>::value_type OutputType;

  komrade::detail::new_value_if<Predicate,T,InputType,OutputType> op(pred,new_value);
  return komrade::transform(first, last, result, op);
} // end replace_copy_if()

namespace detail
{

template<typename ExemplarType, typename InputType>
  struct if_equal_to_exemplar
{
  if_equal_to_exemplar(const ExemplarType &e):exemplar(e){}

  __host__ __device__ bool operator()(const InputType &x) const
  {
    return exemplar == x;
  } // end operator()()

  ExemplarType exemplar;
}; // end if_equal_to_exemplar

}; // end detail

template<typename InputIterator, typename OutputIterator, typename T>
  OutputIterator replace_copy(InputIterator first, InputIterator last,
                              OutputIterator result,
                              const T &old_value,
                              const T &new_value)
{
  typedef typename komrade::iterator_traits<InputIterator>::value_type InputType;

  komrade::detail::if_equal_to_exemplar<T,InputType> pred(old_value);

  return komrade::replace_copy_if(first, last, result, pred, new_value);
} // end replace_copy()

template<typename ForwardIterator, typename Predicate, typename T>
  void replace_if(ForwardIterator first, ForwardIterator last,
                  Predicate pred,
                  const T &new_value)
{
  komrade::replace_copy_if(first, last, first, pred, new_value);
} // end replace_if()

template<typename ForwardIterator, typename T>
  void replace(ForwardIterator first, ForwardIterator last,
               const T &old_value,
               const T &new_value)
{
  komrade::replace_copy(first, last, first, old_value, new_value);
} // end replace()

}; // end komrade

