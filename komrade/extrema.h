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

#pragma once

#include <komrade/detail/config.h>

namespace komrade
{

/*! \file extrema.h
 *  \brief Defines the interface to functions for computing extrema.
 */

/*! \bug The correct form of min does not compile:
 *  const T &min(const T &lhs, const T &rhs, BinaryPredicate comp);
 */
template<typename T, typename BinaryPredicate>
__host__ __device__
  T min(const T &lhs, const T &rhs, BinaryPredicate comp);

/*! \bug The correct form of min does not compile:
 *  const T &min(const T &lhs, const T &rhs);
 */
template<typename T>
__host__ __device__
  T min(const T &lhs, const T &rhs);

/*! \bug The correct form of max does not compile:
 *  const T &max(const T &lhs, const T &rhs, BinaryPredicate comp);
 */
template<typename T, typename BinaryPredicate>
__host__ __device__
  T max(const T &lhs, const T &rhs, BinaryPredicate comp);

/*! \bug The correct form of max does not compile:
 *       const T &max(const T &lhs, const T &rhs);
 */
template<typename T>
__host__ __device__
  T max(const T &lhs, const T &rhs);

/*! \addtogroup reductions
 *  \{
 *  \addtogroup extrema
 *  \ingroup reductions
 *  \{
 */

/*! \p min_element finds the smallest element in the range <tt>[first, last)</tt>.
 *  It returns the first iterator \c i in <tt>[first, last)</tt>
 *  such that no other iterator in <tt>[first, last)</tt> points to a value smaller
 *  than \c *i. The return value is \p last if and only if <tt>[first, last)</tt> is an
 *  empty range.
 *
 *  The two versions of \p min_element differ in how they define whether one element is
 *  less than another. This version compares objects using \c operator<. Specifically,
 *  this version of \p min_element returns the first iterator \c i in <tt>[first, last)</tt>
 *  such that, for every iterator \c j in <tt>[first, last)</tt>, <tt>*j < *i</tt> is
 *  \c false.
 *
 *  \param first The beginning of the sequence.
 *  \param last  The end of the sequence.
 *  \return An iterator pointing to the smallest element of the range <tt>[first, last)</tt>,
 *          if it is not an empty range; \p last, otherwise.
 *
 *  \tparam ForwardIterator is a model of <a href="http://www.sgi.com/tech/stl/ForwardIterator">Forward Iterator</a>,
 *          and \c ForwardIterator's \c value_type is a model of
 *          <a href="http://www.sgi.com/tech/stl/LessThanComparable.html">LessThan Comparable</a>.
 *
 *  \code
 *  #include <komrade/min_element.h>
 *  ...
 *  int data[6] = {1, 0, 2, 2, 1, 3};
 *  int *result = komrade::min_element(data, data + 6);
 *
 *  // *result == 0
 *  \endcode
 *
 *  \see http://www.sgi.com/tech/stl/min_element.html 
 */
template <typename ForwardIterator>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last);

/*! \p min_element finds the smallest element in the range <tt>[first, last)</tt>.
 *  It returns the first iterator \c i in <tt>[first, last)</tt>
 *  such that no other iterator in <tt>[first, last)</tt> points to a value smaller
 *  than \c *i. The return value is \p last if and only if <tt>[first, last)</tt> is an
 *  empty range.
 *
 *  The two versions of \p min_element differ in how they define whether one element is
 *  less than another. This version compares objects using a function object \p comp.
 *  Specifically, this version of \p min_element returns the first iterator \c i in <tt>[first, last)</tt>
 *  such that, for every iterator \c j in <tt>[first, last)</tt>, <tt>comp(*j, *i)</tt> is
 *  \c false.
 *
 *  \param first The beginning of the sequence.
 *  \param last  The end of the sequence.
 *  \param comp A binary predicate used for comparison.
 *  \return An iterator pointing to the smallest element of the range <tt>[first, last)</tt>,
 *          if it is not an empty range; \p last, otherwise.
 *
 *  \tparam ForwardIterator is a model of <a href="http://www.sgi.com/tech/stl/ForwardIterator">Forward Iterator</a>,
 *          and \p ForwardIterator's \c value_type is convertible to both \p comp's
 *          \c first_argument_type and \c second_argument_type.
 *  \tparam BinaryPredicate is a model of <a href="http://www.sgi.com/tech/stl/BinaryPredicate">Binary Predicate</a>.
 *
 *  \see http://www.sgi.com/tech/stl/min_element.html 
 */
template <typename ForwardIterator, typename BinaryPredicate>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last,
                            BinaryPredicate comp);

/*! \p max_element finds the largest element in the range <tt>[first, last)</tt>.
 *  It returns the first iterator \c i in <tt>[first, last)</tt>
 *  such that no other iterator in <tt>[first, last)</tt> points to a value larger
 *  than \c *i. The return value is \p last if and only if <tt>[first, last)</tt> is an
 *  empty range.
 *
 *  The two versions of \p max_element differ in how they define whether one element is
 *  greater than another. This version compares objects using \c operator<. Specifically,
 *  this version of \p max_element returns the first iterator \c i in <tt>[first, last)</tt>
 *  such that, for every iterator \c j in <tt>[first, last)</tt>, <tt>*i < *j</tt> is
 *  \c false.
 *
 *  \param first The beginning of the sequence.
 *  \param last  The end of the sequence.
 *  \return An iterator pointing to the largest element of the range <tt>[first, last)</tt>,
 *          if it is not an empty range; \p last, otherwise.
 *
 *  \tparam ForwardIterator is a model of <a href="http://www.sgi.com/tech/stl/ForwardIterator.html">Forward Iterator</a>,
 *          and \c ForwardIterator's \c value_type is a model of
 *          <a href="http://www.sgi.com/tech/stl/LessThanComparable.html">LessThan Comparable</a>.
 *
 *  \code
 *  #include <komrade/max_element.h>
 *  ...
 *  int data[6] = {1, 0, 2, 2, 1, 3};
 *  int *result = komrade::max_element(data, data + 6);
 *
 *  // *result == 3
 *  \endcode
 *
 *  \see http://www.sgi.com/tech/stl/max_element.html 
 */
template <typename ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last);

/*! \p min_element finds the largest element in the range <tt>[first, last)</tt>.
 *  It returns the first iterator \c i in <tt>[first, last)</tt>
 *  such that no other iterator in <tt>[first, last)</tt> points to a value larger
 *  than \c *i. The return value is \p last if and only if <tt>[first, last)</tt> is an
 *  empty range.
 *
 *  The two versions of \p max_element differ in how they define whether one element is
 *  less than another. This version compares objects using a function object \p comp.
 *  Specifically, this version of \p max_element returns the first iterator \c i in <tt>[first, last)</tt>
 *  such that, for every iterator \c j in <tt>[first, last)</tt>, <tt>comp(*i, *j)</tt> is
 *  \c false.
 *
 *  \param first The beginning of the sequence.
 *  \param last  The end of the sequence.
 *  \param comp A binary predicate used for comparison.
 *  \return An iterator pointing to the largest element of the range <tt>[first, last)</tt>,
 *          if it is not an empty range; \p last, otherwise.
 *
 *  \tparam ForwardIterator is a model of <a href="http://www.sgi.com/tech/stl/ForwardIterator.html">Forward Iterator</a>,
 *          and \p ForwardIterator's \c value_type is convertible to both \p comp's
 *          \c first_argument_type and \c second_argument_type.
 *  \tparam BinaryPredicate is a model of <a href="http://www.sgi.com/tech/stl/BinaryPredicate.html">Binary Predicate</a>.
 *
 *  \see http://www.sgi.com/tech/stl/max_element.html 
 */
template <typename ForwardIterator, typename BinaryPredicate>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last,
                            BinaryPredicate comp);

/*! \} // end extrema
 *  \} // end reductions
 */

} // end komrade

#include <komrade/detail/extrema.inl>
#include <komrade/detail/min_max_element.inl>

