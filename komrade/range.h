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


/*! \file range.h
 *  \brief Fills a sequence with a range of numbers.
 */

#pragma once

#include <komrade/detail/config.h>

namespace komrade
{

/*! \addtogroup transformations
 *  \{
 */

/*! \p range fills the sequence <tt>[first, last)</tt> with a range of numbers.
 *
 *  Specifically, this version of \p range assigns \c *first the value \c 0
 *  and assigns each iterator \c i in the sequence <tt>[first, last)</tt> the
 *  value <tt>(i - first)</tt>.
 *
 *  \param first The beginning of the sequence.
 *  \param last The end of the sequence.
 *
 *  \tparam ForwardIterator is a model of <a href="http://www.sgi.com/tech/stl/ForwardIterator.html">Forward Iterator</a>,
 *          and \p ForwardIterator is mutable,
 *          and if \c x and \c y are objects of \c ForwardIterator's \c value_type, then <tt>x + y</tt> is defined,
 *          and if \c T is \p ForwardIterator's \c value_type, then <tt>T(0)</tt> is defined.
 *
 *  The following code snippet demonstrates how to use \p range to fill a sequence
 *  with a range of numbers.
 *
 *  \code
 *  #include <komrade/range.h>
 *  ...
 *  const int N = 10;
 *  int A[N];
 *  komrade::range(A, A + 10);
 *  // A is now {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
 *  \endcode
 *
 *  \note Unlike the similar C++ STL function \c std::iota, \p range offers no
 *        guarantee on order of execution.
 *
 *  \see http://www.sgi.com/tech/stl/iota.html
 */
template<typename ForwardIterator>
  void range(ForwardIterator first,
             ForwardIterator last);


/*! \p range fills the sequence <tt>[first, last)</tt> with a range of numbers.
 *
 *  Specifically, this version of \p range assigns \c *first the value \p init
 *  and assigns each iterator \c i in the sequence <tt>[first, last)</tt> the
 *  value <tt>init + (i - first)</tt>.
 *
 *  \param first The beginning of the sequence.
 *  \param last The end of the sequence.
 *  \param init The first value of the range of numbers.
 *
 *  \tparam ForwardIterator is a model of <a href="http://www.sgi.com/tech/stl/ForwardIterator.html">Forward Iterator</a>,
 *          and \p ForwardIterator is mutable,
 *          and if \c x and \c y are objects of \c ForwardIterator's \c value_type, then <tt>x + y</tt> is defined,
 *          and if \c T is \p ForwardIterator's \c value_type, then <tt>T(0)</tt> is defined.
 *  \tparam T is a model of <a href="http://www.sgi.com/tech/stl/Assignable.html">Assignable</a>,
 *          and \p T is convertible to \p ForwardIterator's \c value_type.
 *
 *  The following code snippet demonstrates how to use \p range to fill a sequence
 *  with a range of numbers starting from an intial value.
 *
 *  \code
 *  #include <komrade/range.h>
 *  ...
 *  const int N = 10;
 *  int A[N];
 *  komrade::range(A, A + 10, 1);
 *  // A is now {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
 *  \endcode
 *
 *  \note Unlike the similar C++ STL function \c std::iota, \p range offers no
 *        guarantee on order of execution.
 *
 *  \see http://www.sgi.com/tech/stl/iota.html
 */
template<typename ForwardIterator, typename T>
  void range(ForwardIterator first,
             ForwardIterator last,
             T init);


/*! \p range fills the sequence <tt>[first, last)</tt> with a range of numbers.
 *
 *  Specifically, this version of \p range assigns \c *first the value \p init
 *  and assigns each iterator \c i in the sequence <tt>[first, last)</tt> the
 *  <tt>value init + step * (i - first)</tt>.
 *
 *  \param first The beginning of the sequence.
 *  \param last The end of the sequence.
 *  \param init The first value of the range of numbers
 *  \param step The difference between consecutive elements.
 *
 *  \tparam ForwardIterator is a model of <a href="http://www.sgi.com/tech/stl/ForwardIterator.html">Forward Iterator</a>,
 *          and \p ForwardIterator is mutable,
 *          and if \c x and \c y are objects of \c ForwardIterator's \c value_type, then <tt>x + y</tt> is defined,
 *          and if \c T is \p ForwardIterator's \c value_type, then <tt>T(0)</tt> is defined.
 *  \tparam T is a model of <a href="http://www.sgi.com/tech/stl/Assignable.html">Assignable</a>,
 *          and \p T is convertible to \p ForwardIterator's \c value_type.
 *
 *  The following code snippet demonstrates how to use \p range to fill a sequence
 *  with a range of numbers starting from an intial value with a step size.
 *
 *  \code
 *  #include <komrade/range.h>
 *  ...
 *  const int N = 10;
 *  int A[N];
 *  komrade::range(A, A + 10, 1, 3);
 *  // A is now {1, 4, 7, 10, 13, 16, 19, 22, 25, 28}
 *  \endcode
 *
 *  \note Unlike the similar C++ STL function \c std::iota, \p range offers no
 *        guarantee on order of execution.
 *
 *  \see http://www.sgi.com/tech/stl/iota.html
 */
template<typename ForwardIterator, typename T>
  void range(ForwardIterator first,
             ForwardIterator last,
             T init,
             T step);

/*! \} // end transformations
 */

} // end namespace komrade

#include <komrade/detail/range.inl>

