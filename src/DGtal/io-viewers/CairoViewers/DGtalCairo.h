/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#pragma once

/**
 * @file   dgtalCairo.h
 * @author Martial Tola <http://liris.cnrs.fr/martial.tola/>
 * @date   mercredi 25 mai 2011
 * 
 * @brief
 *
 * Header file for module DGtalCairo.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DGtalCairo_RECURSES)
#error Recursive header files inclusion detected in DGtalCairo.h
#else // defined(DGtalCairo_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DGtalCairo_RECURSES

#if !defined DGtalCairo_h
/** Prevents repeated inclusion of headers. */
#define DGtalCairo_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include <algorithm>

#include <map>

#include <QColor>

#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
 /**
   * Base class specifying the methods for classes which intend to
   * modify a DGtalCairo stream.
   * 
   */
  struct DrawWithCairoModifier {
    std::string styleName() const
    {
      return "DrawWithCairoModifier";
    }

    DrawableWithDGtalCairo* defaultStyleCairo( std::string = "" ) const
    {
      return 0;
    }

    virtual void selfDrawCairo( DGtalCairo &  ) const 
    {}
    
};

/////////////////////////////////////////////////////////////////////////////
// class DGtalCairo
/**
 * Description of class 'DGtalCairo' <p>
 * \brief Aim:
 */
  class DGtalCairo
{
    // ----------------------- Standard services ------------------------------
public:
  enum CairoType { CairoPDF, CairoPNG, CairoPS, CairoEPS, CairoSVG };
  
  DGtalCairo();
  
  void setCameraPosition(double x, double y, double z) { camera_position[0] = x; camera_position[1] = y; camera_position[2] = z; }
  void setCameraDirection(double x, double y, double z) { camera_direction[0] = x; camera_direction[1] = y; camera_direction[2] = z; }
  void setCameraUpVector(double x, double y, double z) { camera_upVector[0] = x; camera_upVector[1] = y; camera_upVector[2] = z; }
  void setNearFar(double near, double far) { ZNear = near; ZFar = far; }
  
  void setWireFrame(bool wf) { wireframe = wf; }
  void saveCairo(const char *filename, CairoType type, int width, int height);
   
  enum StreamKey {addNewList, updateDisplay};
  
  /**
   * The associated map type for storing possible modes used for
   * displaying for digital objects.
   */
  typedef std::map< std::string, std::string > ModeMapping;

  /**
   * The associated map type for storing the default styles of
   * digital objects.
   */
  typedef std::map< std::string,CountedPtr<DrawableWithDGtalCairo> > StyleMapping;
  
  QColor myDefaultBackgroundColor;
  QColor myDefaultColor;
  QColor myCurrentFillColor;
  QColor myCurrentLineColor;
  bool myIsBackgroundDefault;

  /**
   * Used to create a new list containing new 3D objects
   * (useful to use transparency between different objects).
   * 
   **/  
  void createNewVoxelList(bool depthTest=true);
  
  /**
   * Used to create a new list containing new 3D objects
   * (useful to use transparency between different objects).
   * 
   **/  
  void createNewLineList();

  /**
   * Used to create a new list containing new 3D objects
   * (useful to use transparency between different objects).
   * 
   **/  
  void createNewPointList();

    /**
     * @param objectName the name of the object (generally obtained
     * with a 'object.styleName()').
     *
     * @return the current mode for the given object name or "" if no
     * specific mode has been set.
     */
    std::string getMode( const std::string & objectName ) const;

  /**
   * Set the default color for future drawing.
   *
   * @param aColor: a QColor (allow to set a trasnparency value).
   *
   **/  
  DGtalCairo & operator<<(const QColor & aColor);
  
  /**
   * Set the default color for future drawing.
   *
   * @param aColor: a QColor (allow to set a trasnparency value).
   *
   **/
  DGtalCairo & operator<<(const DGtalCairo::StreamKey  & key);

  /**
   *  Add a point as a 3d voxel using default color in the current list.
   *  A voxel can be added in a new list by calling: @createNewList().
   *  @param aPoint: the center of the voxel.
   *  @param width: the width of the voxel (default 0.5)
   *
   **/
  void addVoxel(int x, int y, int z, QColor color= QColor(220, 220, 220), double width=0.5);
  
  void addPoint(double x, double y, double z ,const QColor &color=QColor(200,20,20), double size=40);

  
  void addLine(double x1, double y1, double z1, double x2, double y2, double z2, 
	       const QColor &color=QColor(20,20,20,200), double width=1.5);
  
 
  void addQuad(double x1, double y1, double z1,  double x2, double y2, double z2,
  	       double x3, double y3, double z3,  double x4, double y4, double z4, QColor aColor);

  
  void addKSSurfel(double x1, double y1, double z1,  double x2, double y2, double z2,
		   double x3, double y3, double z3,  double x4, double y4, double z4, QColor aColor=QColor(180,180,250,255));

  void addKSVoxel(int x, int y, int z, const QColor &aColor=QColor(255,180,250,255));
  
  void addKSPointel(double x, double y, double z, double size=0.1, const QColor &color=QColor(200,20,20,255));
  
  void addKSLinel(double x1, double y1, double z1,
		  double x2, double y2, double z2,
		  double width=0.02, const QColor &color=QColor(20,20,200,255));

  /**
   * Add a new 3D Clipping plane represented by ax+by+cz+d = 0 
   * A maximal of five clipping plane can be added.
   *
   * @param a, b, c, d : plane equation.
   **/
  void addClippingPlane(double a, double b, double c, double d, bool drawPlane);

  void setLineColor(QColor aColor) ;
  QColor getLineColor() ;

  void setFillColor(QColor aColor) ;
  QColor getFillColor() ;

  /**
   * Draws the drawable [object] in this board. It should satisfy
   * the concept CDrawableWithDGtalCairo, which requires for instance a
   * method selfDraw( DGtalCairo & ).
   *
   * @param object any drawable object.
   * @return a reference on 'this'.
   */
  template <typename TDrawableWithDGtalCairo>
  DGtalCairo & operator<<( const  TDrawableWithDGtalCairo & object );

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

  // ------------------------- Protected Datas ------------------------------
private:

public:
  
  ModeMapping myModes;  
      /**
     * For instance, may associate a new style object T1 to the class
     * "HyperRectDomain": myStyles[ "HyperRectDomain" ] = T1.
     *
     * One can also store a new style T2 for a specific mode used for
     * drawing a class:  myStyles[ "HyperRectDomain/Paving" ] = T2.
     *
     * Modes may only be used in objects implementing the concept
     * CDrawableWithDGtalBoard.
     */
    StyleMapping myStyles;

    // ------------------------- Private Datas --------------------------------
private:
  
  struct lineGL{
    double x1, y1, z1;
    double x2, y2, z2;
    double width;
    unsigned int R,G,B,T;
  };
    
  struct voxelGL{
    int x, y,z;
    unsigned int R,G,B,T;
    double width;
  };
  
  struct pointGL{
    double  x, y,z;
    unsigned int R,G,B,T;
    double size;
  };
  
  struct clippingPlaneGL{
    double a,b,c,d;
  };

  struct  quadGL{
    double x1,y1,z1;
    double x2,y2,z2;
    double x3,y3,z3;
    double x4,y4,z4;    
    unsigned int R,G,B,T;
  };
    
  // Used to represent all the list used in the display.
  std::vector< std::vector<voxelGL> > myVoxelSetList;
  
  // Used to represent all the list of line primitive
  std::vector< std::vector<lineGL> > myLineSetList;
  
  // Used to represent all the list of line primitive
  std::vector< std::vector<pointGL> > myPointSetList;

  // Represent all the clipping planes added to the scene (of maxSize=5).
  std::vector< clippingPlaneGL > myClippingPlaneList;
  
  // For saving all voxels of Khalimsky space (used to display Khalimsky Space Cell)
  // see. myVoxelSetList (first vector)
  
  // For saving all surfels of Khalimsky space (used to display Khalimsky Space Cell)
  std::vector< quadGL > myKSSurfelList;

  // For saving all pointels of Khalimsky space (used to display Khalimsky Space Cell)
  std::vector< pointGL > myKSPointelList;

  // For saving all linels of Khalimsky space (used to display Khalimsky Space Cell)
  std::vector< lineGL > myKSLinelList;

  // Represent all the drawed planes
  std::vector< quadGL > myQuadList;
  
  //Used to define if GL_TEST_DEPTH is used. 
  std::vector<bool> myListVoxelDepthTest;
  
  unsigned int myNbListe;
  
  void precompute_projection_matrix();
  void project(double x3d, double y3d, double z3d, double &x2d, double &y2d);
  
  int Viewport[4];
  double matrix[16];
      
  double camera_position[3];
  double camera_direction[3];
  double camera_upVector[3];
  
  double ZNear;
  double ZFar;
  
  bool wireframe;
  
    // ------------------------- Hidden services ------------------------------
protected :
  virtual void init();

    // ------------------------- Internals ------------------------------------
private:

  }; // end of class DGtalCairo

 /**
   * Modifier class in a DGtalCairo stream. Useful to choose your
   * own mode for a given class. Realizes the concept
   * CDrawableWithDGtalCairo.
   */
  struct SetMode3DCairo : public DrawWithCairoModifier {
    /**
     * @param classname the name of the class to which the style is associated.
     *
     * @param style a pointer on a dynamically allocated style, which
     * is acquired by the class.
     */
    SetMode3DCairo( std::string classname, std::string mode )
      : myClassname( classname ), myMode( mode )
    {}
    void selfDrawCairo( DGtalCairo & viewer ) const
    {
      viewer.myModes[ myClassname ] = myMode;
    }
  private:
    std::string myClassname;
    std::string myMode;
  };

  /**
   * Modifier class in a DGtalCairo stream. Useful to choose your own
   * style for a given class. Realizes the concept
   * CDrawableWithDGtalCairo.
   */
  struct CustomStyle3DCairo : public DrawWithCairoModifier {
    /**
     * @param classname the name of the class to which the style is associated.
     *
     * @param style a pointer on a dynamically allocated style, which
     * is acquired by the class.
     */
    CustomStyle3DCairo( std::string classname, DrawableWithDGtalCairo* style )
      : myClassname( classname ), myStyle( style )
    {}

    std::string styleName() const
    {
      return "CustomStyle3D";
    }

    void selfDrawCairo( DGtalCairo & viewer ) const
    {
      viewer.myStyles[ myClassname ] = myStyle;
    }
  private:
    std::string myClassname;
    CountedPtr<DrawableWithDGtalCairo> myStyle;
  };

  /**
   * Custom style class redefining the fill color and the
   * gl_LINE/gl_POINT color. You can use Qcolor with alpha
   * transparency value but you nedd to take into account the z-buffer
   * during the Open-GL based rendering.
   *
   */
  struct CustomColors3DCairo : public DrawWithCairoModifier
  {
    QColor myPenColor;
    QColor myFillColor;

    /**
     * Constructor.
     *
     * @param penColor specifies the pen color.
     * @param fillColor specifies the fill color.
     */
    CustomColors3DCairo( const QColor & penColor,
		    const QColor & fillColor )
      : myPenColor( penColor ), myFillColor( fillColor )
    {}
    
    virtual void selfDrawCairo( DGtalCairo & viewer) const
    {
      viewer.setFillColor(myFillColor);
      viewer.setLineColor(myPenColor);
    }
  };

 /**
   * Class for adding a Clipping plane through the DGtalCairo
   * stream. Realizes the concept CDrawableWithDGtalCairo.
   */
  struct ClippingPlaneCairo : public DrawWithCairoModifier {
    /**
     * @param classname the name of the class to which the style is associated.
     *
     * @param style a pointer on a dynamically allocated style, which
     * is acquired by the class.
     */
    ClippingPlaneCairo( double a, double b, double c, double d, bool drawPlane=true )
      : myA( a ), myB( b ), myC( c ), myD ( d ), myDrawPlane(drawPlane)  
    {}
    void selfDrawCairo( DGtalCairo & viewer ) const
    {
      viewer.addClippingPlane(myA, myB, myC, myD, myDrawPlane);
      
    }
    double * getEquation(){
      double *r = new double[4];
      r[0] = myA;
      r[1] = myB;
      r[2] = myC;
      r[3] = myD;
      return r;
    } 
  
  private:
    double myA;
    double myB;
    double myC;
    double myD;
    bool myDrawPlane;
    
  };

/**
 * Overloads 'operator<<' for displaying objects of class 'DGtalCairo'.
 * @param out the output stream where the object is written.
 * @param object the object of class 'DGtalCairo' to write.
 * @return the output stream after the writing.
 */
std::ostream&
operator<< ( std::ostream & out, const DGtalCairo & object );

} // namespace DGtal

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions/methods if necessary.
#if defined(INLINE)
#include "DGtal/io-viewers/CairoViewers/DGtalCairo.ih"
#endif

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DGtalCairo_h

#undef DGtalCairo_RECURSES
#endif // else defined(DGtalCairo_RECURSES)
