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
 * Face.h
 *
 *  Created on: 20 f??vr. 2014
 *      Author: ledouxf
 */
/*----------------------------------------------------------------------------*/
#ifndef GMDS_FACE_H_
#define GMDS_FACE_H_
/*----------------------------------------------------------------------------*/
#include <GMDS/IG/Cell.h>
#include <GMDS/Math/VectorND.h>
/*----------------------------------------------------------------------------*/
namespace gmds{
	/*----------------------------------------------------------------------------*/
	class IGMesh;
	class FaceContainer;
	/*----------------------------------------------------------------------------*/
	/** \class Face
	 *
	 *  \brief A face instance is an object that provided an object-type access to
	 *  	   the data representing a mesh face.
	 *
	 */
	class EXPORT_GMDS Face : public Cell{
	public:

		/*------------------------------------------------------------------------*/
		/** \brief Default constructor. Used for stl container initialization
		 */
		Face();

		/*------------------------------------------------------------------------*/
		/** \brief Constructor
		 *
		 * \param AMesh the mesh containing this cell
		 * \param AType the type of cell
		 * \param AID the cell id
		 */
		Face(IGMesh* AMesh, const ECellType AType, const TCellID& AID);

		/*------------------------------------------------------------------------*/
		/** \brief Copy Constructor
		 *
		 * \param AF the face to be copied
		 */
		Face(const Face& AF);


		void operator=(const Face& AFace);

		/*------------------------------------------------------------------------*/
		/** \brief Overide operator==. It is id-based.
		 *
		 * \param AFace a face
		 */
		bool operator==(const Face& AFace) const;

		/*------------------------------------------------------------------------*/
		/** \brief Overide operator==. It is id-based.
		 *
		 * \param AFace a face
		 */
		bool operator!=(const Face& AFace) const;

		/*------------------------------------------------------------------------*/
		/** \brief Overide operator<. It is id-based.
		 *
		 * \param AFace a face
		 */
		bool operator<(const Face& AFace) const { return this->m_id < AFace.m_id; }

		/*------------------------------------------------------------------------*/
		/** \brief Destructor
		 */
		virtual ~Face();

		inline TInt getTypeID() const { return m_type_id; }
		/*------------------------------------------------------------------------*/
		/** \brief  Accesor to the cell dim.
		 */
		virtual int getDim() const { return 2; }

		/*------------------------------------------------------------------------*/
		/** \brief Accessor th the number of incident nodes, edges, faces and
		 * 		   adjacent regions
		 */
		virtual TInt getNbNodes()   const;
		virtual TInt getNbEdges()   const;
		virtual TInt getNbFaces()   const;
		virtual TInt getNbRegions() const;

		/*------------------------------------------------------------------------*/
                /** \brief Compute the normal of the face.
                 */
		math::Vector normal() const;

		/*------------------------------------------------------------------------*/
                /** \brief Compute the normal of the face (triangle that contains ANode).
		 *
		 * \param ANode the node from which the normal will be computed
                 */
                math::Vector normal(const Node& ANode) const;

		/*------------------------------------------------------------------------*/
                /** \brief Compute the center of the face
                 */
		math::Point center() const;

		/*------------------------------------------------------------------------*/
                /** \brief Compute the area of the face
		 * 
		 * \return the area of the face
                 */
		TCoord area() const;

		/*------------------------------------------------------------------------*/
	        /** \brief  Compute the scaled jacobian of the face
        	 *
	         * \return the scaled jacobian
        	 */
	        double computeScaledJacobian2D() const;

		/*------------------------------------------------------------------------*/
		/** \brief  compute the shortest distance from a point to this.
		 *
		 * 			WARNING: only implemented for triangular faces.
		 *
		 * 			We use the orthogonal projection to the plane containing
		 * 			(*this). If the projected point is in the triangle, we keep
		 * 			it to compute the distance to AP. Otherwise, we project AP
		 * 			onto the closest edge of (*this).
		 *
		 * \param AP a point
		 *
		 * \return the distance
		 */
		TCoord distance(const math::Point& AP) const;
		/*------------------------------------------------------------------------*/
		/** \brief  Orthogonal projection of a point AP onto this.
		 *
		 * 			WARNING: only implemented for triangular faces.
		 *
		 * \param AP a point
		 *
		 * \return the orthogonal projection of AP onto T
		 */
		math::Point project(const math::Point& AP) const;

		/*------------------------------------------------------------------------*/
		/** \brief  Provide the nodes adjacent to ANode1
		 *
		 *  \param ANode1 incoming node
		 *  \param ANode2 first adjacent node in this
		 *  \param ANode3 second adjacent node in this
		 */
		void getAdjacentNodes(const Node& ANode1, Node& ANode2, Node& ANode3);

		/*------------------------------------------------------------------------*/
                /** \brief  Provide the edges in an ordered fashion. Same order as the nodes
                 *
                 *  \param AEdges the container of the ordered edges
                 */
                void getOrderedEdges(std::vector<Edge>& AEdges) const;

		/*------------------------------------------------------------------------*/
		/** \brief  Accessor to the incident cells. Only the non-null cells are
		 * 			provided. T can be Node, Edge, Face or Region.
		 */
		virtual void delegateGet(std::vector<Node>&   ACells) const;
		virtual void delegateGet(std::vector<Edge>&   ACells) const;
		virtual void delegateGet(std::vector<Face>&   ACells) const;
		virtual void delegateGet(std::vector<Region>& ACells) const;

		virtual void delegateGetNodeIDs(std::vector<TCellID>& ACells) const;
		virtual void delegateGetEdgeIDs(std::vector<TCellID>& ACells) const;
		virtual void delegateGetFaceIDs(std::vector<TCellID>& ACells) const;
		virtual void delegateGetRegionIDs(std::vector<TCellID>& ACells) const;

		virtual void delegateGetAll(std::vector<Node>&   ACells) const;
		virtual void delegateGetAll(std::vector<Edge>&   ACells) const;
		virtual void delegateGetAll(std::vector<Face>&   ACells) const;
		virtual void delegateGetAll(std::vector<Region>& ACells) const;

		virtual void delegateGetAllNodeIDs(std::vector<TCellID>& ACells) const;
                virtual void delegateGetAllEdgeIDs(std::vector<TCellID>& ACells) const;
                virtual void delegateGetAllFaceIDs(std::vector<TCellID>& ACells) const;
                virtual void delegateGetAllRegionIDs(std::vector<TCellID>& ACells) const;

		virtual void delegateSetNodeIDs(const std::vector<TCellID>& ACells);
		virtual void delegateSetEdgeIDs(const std::vector<TCellID>& ACells);
		virtual void delegateSetFaceIDs(const std::vector<TCellID>& ACells);
		virtual void delegateSetRegionIDs(const std::vector<TCellID>& ACells);

		virtual void delegateNodeAdd(TCellID AElt);
		virtual void delegateEdgeAdd(TCellID AElt);
		virtual void delegateFaceAdd(TCellID AElt);
		virtual void delegateRegionAdd(TCellID AElt);

		virtual void delegateNodeRemove(TCellID AElt);
		virtual void delegateEdgeRemove(TCellID AElt);
		virtual void delegateFaceRemove(TCellID AElt);
		virtual void delegateRegionRemove(TCellID AElt);

		virtual void delegateNodeReplace(TCellID AID1, TCellID AID2);
		virtual void delegateEdgeReplace(TCellID AID1, TCellID AID2);
		virtual void delegateFaceReplace(TCellID AID1, TCellID AID2);
		virtual void delegateRegionReplace(TCellID AID1, TCellID AID2);

		friend std::ostream & operator << (std::ostream & AStream, const Face& AN);

	protected:

		/** A link to the generic face container of the owner*/
		FaceContainer* m_faces_container;

		/** type-id */
		TCellID m_type_id;
	};
	/*----------------------------------------------------------------------------*/
} // namespace gmds
/*----------------------------------------------------------------------------*/
#endif /* GMDS_FACE_H_ */
/*----------------------------------------------------------------------------*/

