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
//
//  Line.cpp

/*----------------------------------------------------------------------------*/
#include <GMDS/Math/Line.h>
/*----------------------------------------------------------------------------*/
#include <GMDS/Math/Segment.h>
#include <GMDS/Math/Plane.h>
#include <GMDS/Math/Triangle.h>
/*----------------------------------------------------------------------------*/
namespace gmds{
    /*--------------------------------------------------------------------------*/
    namespace math{
        /*------------------------------------------------------------------------*/
        const Point& Line::getFirstPoint() const
        {
            return m_p1;
        }
        /*------------------------------------------------------------------------*/
        const Point& Line::getSecondPoint() const
        {
            return m_p2;
        }
        /*------------------------------------------------------------------------*/
        Line& Line::operator=(const Line& AL) {
            m_p1 = AL.m_p1;
            m_p2 = AL.m_p2;
            return *this;
        }
        /*----------------------------------------------------------------------------*/
        bool Line::intersect2D(const Line& AL, Point& AP, double& AParam) const {
            
            Point  p1= AL.getFirstPoint();
            Point  p2= AL.getSecondPoint();
            
            Point src_pnt = m_p1;
            Point dir_pnt = m_p2;
            
            Vector v12(p1,p2);
            Vector vsc(src_pnt,dir_pnt);
            if(v12.isColinear(vsc)){
                return false; // No intersection
            }
            
            double x1 = p1.X();
            double y1 = p1.Y();
            double x2 = p2.X();
            double y2 = p2.Y();
            double xs = src_pnt.X();
            double ys = src_pnt.Y();
            double xd = dir_pnt.X();
            double yd = dir_pnt.Y();
            
            double D = x1*(yd-ys) + x2*(ys-yd) + xd*(y2-y1) + xs* (y1-y2);
            double N = x1*(yd-ys) + xs*(y1-yd) + xd*(ys-y1);
            
            //param in [p1,p2]
            double s = N/D;
            
            N =  -(x1*(ys- y2) + x2*(y1-ys) + xs*(y2-y1));
            
            //param in [src_pnt,dir_pnt]
            double t = N/D;
            
            if ((0.0 <= s) && (s <= 1.0) && (0.0 < t)){
                AP = p1 + s*(p2-p1);
                AParam = 1-s;
                return true;
            }
            return false;
            
        }

/*----------------------------------------------------------------------------*/
bool Line::intersect3D(const Plane& APlane, Point& AP, double& AParam) const
{
	Point src = m_p1;
	Vector dir(m_p1, m_p2);

	Vector normal = APlane.getNormal();
	Vector w0(APlane.getPoint(),src);

	double a = - normal.dot(w0);
	double b = normal.dot(dir);

	if(b == 0.) {
		return false; // line is parallel to the plane
	}
	
	// compute intersection point with plane
	AParam = a/b;
	AP = gmds::math::Point(src+AParam*dir);
	return true;
}
/*----------------------------------------------------------------------------*/
bool Line::intersect3D(const Triangle& ATri, Point& AP, double& AParam) const
{
	// check whether the line intersects the plane of the triangle
	Plane pl = ATri.getPlaneIncluding();
	if(!this->intersect3D(pl,AP,AParam)) {
		return false;
	}
	
	// check whether the intersection point is inside the triangle
	if(ATri.isIn(AP)) {
		return true;
	} else {
		return false;
	}
}
        
        /*----------------------------------------------------------------------------*/
        Point Line::project(const Point& AP) const {
            
            Vector v1(m_p1, m_p2), v2(m_p1, AP);
            
            TCoord a = v1.dot(v2), b = v1.dot(v1);
            
            return m_p1 + (a/b) * v1;
        }
        
        
        /*----------------------------------------------------------------------------*/
        TCoord Line::distance2D(const Segment &AS, Point& AP1, Point& AP2) const {
            
            TCoord distance = 0;
            
            Point  p1= AS.getPoint(0);
            Point  p2= AS.getPoint(1);
            
            Point src_pnt = m_p1;
            Point dir_pnt = m_p2;
            
            Vector v12(p1,p2);
            Vector vsc(src_pnt,dir_pnt);
            if(v12.isColinear(vsc)){
                //===========================================
                // No intersection, parallel case
                Point proj = project(p1);
                if(proj==p1){
                    //segment in on the line!!!!
                    AP1 = p1;
                    AP2 = p1;
                    distance = 0;
                }
                else {
                    AP1 = proj;
                    AP2 = p1;
                    distance = AP1.distance(AP2);
                }
            }
            else {
                //===========================================
                //can intersect
                //compute the intersection point
                double x1 = p1.X(); //segment point
                double y1 = p1.Y(); //segment point
                double x2 = p2.X(); //segment point
                double y2 = p2.Y(); //segment point
                double xs = src_pnt.X(); //line point
                double ys = src_pnt.Y(); //line point
                double xd = dir_pnt.X(); //line point
                double yd = dir_pnt.Y(); //line point
                
                double D = x1*(yd-ys) + x2*(ys-yd) + xd*(y2-y1) + xs* (y1-y2);
                double N = x1*(yd-ys) + xs*(y1-yd) + xd*(ys-y1);
                
                //param in [p1,p2]
                double s = N/D;
                
                N =  -(x1*(ys- y2) + x2*(y1-ys) + xs*(y2-y1));
                
                if ((0.0 <= s) && (s <= 1.0)){
                    // the segment intersects the line
                    AP1 = p1 + s*(p2-p1);
                    AP2 = AP1;
                    distance = 0;
                }
                else {
                    //there is no intersection, the closest point is so p1 or p2
                    Point proj1 = project(p1);
                    Point proj2 = project(p2);
                    TCoord d1 = p1.distance(proj1);
                    TCoord d2 = p2.distance(proj2);
                    if(d1<=d2){
                        AP1 = proj1;
                        AP2 = p1;
                        distance =d1;
                    }
                    else {
                        AP1 = proj2;
                        AP2 = p2;
                        distance =d2;
                        
                    }
                }//else
                
            }//else
            
            return distance;
        }
        
        
        /*----------------------------------------------------------------------------*/
    } // namespace math
    /*----------------------------------------------------------------------------*/
} // namespace gmds
/*----------------------------------------------------------------------------*/
