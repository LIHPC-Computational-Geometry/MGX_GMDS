/*----------------------------------------------------------------------------*/
/* Copyright: CEA
 * contributors: F. Ledoux (2015)
 *
 * franck.ledoux@cea.fr
 *
 * The FRAME software is a computer program whose purpose is to provide a set
 * of algorithms to build 2D and 3D meshes using frame field concept. The main
 * focus of these algorithms is quadrilateral and hexahedral meshing.
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
#ifndef SH_EIGEN_FIELD_SOLVER_STRATEGY_H_
#define SH_EIGEN_FIELD_SOLVER_STRATEGY_H_
/*----------------------------------------------------------------------------*/
// STL File Headers
/*---------------------------------------------------------------------------*/
// Frame File Headers
#include "FieldSolverStrategyItf.h"
/*----------------------------------------------------------------------------*/
namespace  fhedo {
/*----------------------------------------------------------------------------*/
/** \class  EigenFieldSolverStrategy
 *  \brief  Implementation of the FieldSolverStrategyItf interface used by an
 *          FieldGenerator object to build a frame field.
 */
class EXPORT_GMDS EigenFieldSolverStrategy: public FieldSolverStrategyItf {
public:
    
    /*------------------------------------------------------------------------*/
    /** \brief Default constructor
     */
    EigenFieldSolverStrategy();
    
    /*------------------------------------------------------------------------*/
    /** \brief Function to be called for solving the system
     */
    virtual void solve();
    virtual void addSmoothingTerms();
    virtual void addBoundaryConstraints();
    virtual void addLockedTerms();
    virtual void initializeAssembly();
    virtual void finalizeAssembly();
    virtual void clean();
    virtual void setX();
    virtual void addLocalOptimConstraints();
    virtual void getFeasibleSolution();
private:
    //    int m_equation_numbering;
    //
    //    /*** Matrix A of the ||AX-b||^2 */
    //    Eigen::SparseMatrix<double> m_A;
    //    /*** Vector X of the ||AX-b||^2 */
    //    Eigen::VectorXd m_X;
    //    /*** Vector b of the ||AX-b||^2 */
    //    Eigen::VectorXd m_b;
    

    
};
/*----------------------------------------------------------------------------*/
}
/*----------------------------------------------------------------------------*/
#endif /* SH_EIGEN_FIELD_SOLVER_STRATEGY_H_ */
/*----------------------------------------------------------------------------*/
