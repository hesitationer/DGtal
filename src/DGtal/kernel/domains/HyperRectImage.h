#pragma once

/**
 * @file HyperRectImage.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/06/09
 *
 * Header file for module HyperRectImage.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(HyperRectImage_RECURSES)
#error Recursive header files inclusion detected in HyperRectImage.h
#else // defined(HyperRectImage_RECURSES)
/** Prevents recursive inclusion of headers. */
#define HyperRectImage_RECURSES

#if !defined HyperRectImage_h
/** Prevents repeated inclusion of headers. */
#define HyperRectImage_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// class HyperRectImage
/**
 * Description of class 'HyperRectImage' <p>
 * Aim:
 *
 *
 *  \todo ajouter un parametre template avec le Container (vector, map, ..) et faire des specialisations spécifiques des iterateurs.
 *  
 */

template < class THyperRectDomain, typename TValue>
class HyperRectImage
{

// ----------------------- Standard services ------------------------------
public:

    /**
    * Constructor.
    * Forbidden by default (protected to avoid g++ warnings).
    */
    HyperRectImage( const typename THyperRectDomain::PointType &aPointA, const typename THyperRectDomain::PointType &aPointB );

    /**
     * Destructor.
     */
    ~HyperRectImage();

    // ----------------------- Interface --------------------------------------
public:


    /**
    * Writes/Displays the object on an output stream.
    * @param out the output stream where the object is written.
    */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

protected:

    THyperRectDomain myDomain; ///Local copie of the HyperRectDomain

    std::vector<TValue> myImageMap; ///Image Container

private:
    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    HyperRectImage & operator= ( const HyperRectImage & other );

    // ------------------------- Internals ------------------------------------
private:

}; // end of class HyperRectImage


/**
 * Overloads 'operator<<' for displaying objects of class 'HyperRectImage'.
 * @param out the output stream where the object is written.
 * @param object the object of class 'HyperRectImage' to write.
 * @return the output stream after the writing.
 */
template <class THyperRectDomain, typename T>
std::ostream&
operator<< ( std::ostream & out, const HyperRectImage<THyperRectDomain,T> & object );


} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined HyperRectImage_h

#undef HyperRectImage_RECURSES
#endif // else defined(HyperRectImage_RECURSES)
