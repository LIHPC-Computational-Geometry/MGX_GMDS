/*----------------------------------------------------------------------------*/
/* Copyright: CEA
 * contributors: F. Ledoux and N. Le Goff (2015)
 *
 * franck.ledoux@cea.fr
 * nicolas.le-goff@cea.fr
 *
 * The GMDS library is a computer program whose purpose is to provide a set of
 * functionnalities to represent and handle any type of meshes (2D, 3D,
 * triangles, tetrahedra, quad, hexa, polygons, polyhedra, etc.) and write
 * meshing algorithms. So it gathers many mathematical objects like points,
 * segment, quaternions, etc. and basic algorithms useful to build more evolved
 * ones.
 *
 * This software is governed by the CeCILL-C license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL-C
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info". 
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability. 
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security. 
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-C license and that you accept its terms.
 */
/*----------------------------------------------------------------------------*/
/*
 * Tetrahedron.h
 *
 *  Created on: 27 nov 2014
 *      Author: legoff
 */
/*----------------------------------------------------------------------------*/
#ifndef GMDS_MATH_TETRAHEDRON_H_
#define GMDS_MATH_TETRAHEDRON_H_
/*----------------------------------------------------------------------------*/
#include <iostream>
/*----------------------------------------------------------------------------*/
// gmds file headers
/*----------------------------------------------------------------------------*/
#include <GMDS/Utils/CommonTypes.h>
#include <GMDS/Math/Point.h>
#include <GMDS/Math/Matrix.h>
/*----------------------------------------------------------------------------*/
namespace gmds{
/*----------------------------------------------------------------------------*/
namespace math{
/*----------------------------------------------------------------------------*/
class Triangle;
/*----------------------------------------------------------------------------*/
/** \class Tetrahedron
 *  \brief Defines a tetrahedron
 */
/*----------------------------------------------------------------------------*/
	class EXPORT_GMDS Tetrahedron
{

public:

	/*------------------------------------------------------------------------*/
	/** \brief  constructor
	 *
	 */
	Tetrahedron();

	/*------------------------------------------------------------------------*/
	/** \brief  constructor
  	 *
  	 * \param AP0 a point of the tet
  	 * \param AP1 a point of the tet
  	 * \param AP2 a point of the tet
  	 * \param AP3 a point of the tet
  	 *
  	 *	                     3__
  	 *                          / \ \____
  	 *	        	  _/   \     2
  	 * 		        _/      \   /
  	 *		       /         \ /
  	 *		     0 -----------1
	 */
	Tetrahedron(const Point& AP0, const Point& AP1, const Point& AP2, const Point& AP3);

	/*------------------------------------------------------------------------*/
        /** \brief  constructor
         *
         * \param APoints an array of points
         *
         */
        Tetrahedron(Point APoints[4]);

	/*------------------------------------------------------------------------*/
        /** \brief  constructor
         *
         * \param APoints a vector of points
         *
         */
        Tetrahedron(const std::vector<Point>& APoints);

	/*------------------------------------------------------------------------*/
	/** \brief  constructor
	 *
	 * \param ATet a tet
	 *
	 */
	Tetrahedron(const Tetrahedron& ATet);

	/*------------------------------------------------------------------------*/
	/** \brief  destructor
	 */
	virtual ~Tetrahedron();

        /*------------------------------------------------------------------------*/
        /** \brief  operator=
         */
        void operator=(const Tetrahedron& ATet);


	/*------------------------------------------------------------------------*/
	/** \brief  Getter for the Tetrahedron point
	 *
	 * \param AIndex an integer
	 *
	 * \return a point
	 */
	const Point& getPoint(const TInt& AIndex) const;
    
    /*------------------------------------------------------------------------*/
    /** \brief  Compute the center of the tetrahedron
     *
     * \return a point
     */
    const Point getCenter() const;
    
    /*------------------------------------------------------------------------*/
    /** \brief  Compute the signed volume of the tetrahedron
     *
     * \return the signed volume of the tetrahedron
     */
    const TCoord getVolume() const;

        /*------------------------------------------------------------------------*/
        /** \brief  Compute the scaled jacobian of the tetrahedron.
         *
         * \return the scaled jacobian
         */
        double computeScaledJacobian() const;

	/*------------------------------------------------------------------------*/
        /** \brief  Compute the scaled jacobian of the tetrahedron
	 *          normalized between [-1., 1.]
         *
         * \return the scaled jacobian
         */
        double computeNormalizedScaledJacobian() const;

	/*------------------------------------------------------------------------*/
        /** \brief  Compute the mean ratio of the tetrahedron.
         *
         * \return the mean ratio
         */
        double computeMeanRatio() const;

	/*------------------------------------------------------------------------*/
        /** \brief  Compute the mean edge length of the tetrahedron.
         *
         * \return the mean edge length
         */
        double computeMeanEdgeLength() const;

        /*------------------------------------------------------------------------*/
        /** \brief  predicate indicating if a triangle and a tet intersect each
 	 *          other.
         * \param AT a triangle
         */
        bool intersect(const Triangle& AT, const bool AProper = false) const;

        /*------------------------------------------------------------------------*/
        /** \brief  Overloaded operator<< for output
         */
        friend std::ostream& operator<<(std::ostream&, const Tetrahedron&);


protected:

        /*------------------------------------------------------------------------*/
        /** \brief  Return the jacobian matrix.
         *
         * \return the jacobian matrix
         */
        math::Matrix<3,3,double> jacobian() const;


	Point m_pnts[4];

};
/*----------------------------------------------------------------------------*/
} // namespace math
/*----------------------------------------------------------------------------*/
} // namespace gmds
/*----------------------------------------------------------------------------*/
#endif /* GMDS_MATH_TETRAHEDRON_H_ */
/*----------------------------------------------------------------------------*/
