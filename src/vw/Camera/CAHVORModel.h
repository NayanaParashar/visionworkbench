// __BEGIN_LICENSE__
// 
// Copyright (C) 2006 United States Government as represented by the
// Administrator of the National Aeronautics and Space Administration
// (NASA).  All Rights Reserved.
// 
// Copyright 2006 Carnegie Mellon University. All rights reserved.
// 
// This software is distributed under the NASA Open Source Agreement
// (NOSA), version 1.3.  The NOSA has been approved by the Open Source
// Initiative.  See the file COPYING at the top of the distribution
// directory tree for the complete NOSA document.
// 
// THE SUBJECT SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY OF ANY
// KIND, EITHER EXPRESSED, IMPLIED, OR STATUTORY, INCLUDING, BUT NOT
// LIMITED TO, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL CONFORM TO
// SPECIFICATIONS, ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
// A PARTICULAR PURPOSE, OR FREEDOM FROM INFRINGEMENT, ANY WARRANTY THAT
// THE SUBJECT SOFTWARE WILL BE ERROR FREE, OR ANY WARRANTY THAT
// DOCUMENTATION, IF PROVIDED, WILL CONFORM TO THE SUBJECT SOFTWARE.
// 
// __END_LICENSE__

/// \file CAHVOR.h
/// 
/// This file contains the CAHVOR pinhole camera model.  This camera
/// model is a refinement of the \ref CAHVModel: it adds extra terms
/// to model basic radial camera distortion.
/// 
#ifndef __VW_CAMERAMODEL_CAHVOR_H__
#define __VW_CAMERAMODEL_CAHVOR_H__

#include <vw/Camera/CameraModel.h>
#include <vw/Camera/CAHVModel.h>

#include <vw/Image/ImageView.h>
#include <vw/Math/Matrix.h>
#include <vw/Math/Vector.h>

#include <string>

namespace vw { 
namespace camera {

  class CAHVORModel : public CameraModel {
  public:
    //------------------------------------------------------------------
    // Constructors / Destructors
    //------------------------------------------------------------------

    /// Default constructor creates CAHVOR vectors equal to 0.
    CAHVORModel() {}
    
    /// Read a CAHVOR file from disk.
    CAHVORModel(std::string const& filename);

    /// Initialize the CAHVOR vectors directly in the native CAHVOR format.
    CAHVORModel(Vector3 C_vec, Vector3 A_vec, Vector3 H_vec, Vector3 V_vec,
                Vector3 O_vec, Vector3 R_vec) : 
      C(C_vec), A(A_vec), H(H_vec), V(V_vec), O(O_vec), R(R_vec) {}

    virtual ~CAHVORModel() {}

    //------------------------------------------------------------------
    // Methods
    //------------------------------------------------------------------
    virtual Vector2 point_to_pixel(Vector3 const& point) const;
    virtual Vector3 pixel_to_vector(Vector2 const& pix) const;
    virtual Vector3 camera_center(Vector2 const& pix = Vector2() ) const { return C; };

    // Overloaded versions also return partial derviatives in a Matrix.
    Vector2 point_to_pixel(Vector3 const& point, Matrix<double> &partial_derivatives) const;
    Vector3 pixel_to_vector(Vector2 const& pix, Matrix<double> &partial_derivatives) const;
      
    //------------------------------------------------------------------
    // Exposed Variables
    //------------------------------------------------------------------
    Vector3   C;
    Vector3   A;
    Vector3   H;
    Vector3   V;
    Vector3   O;
    Vector3   R;
  };
  
  /// Function to "map" the CAHVOR parameters into CAHV parameters:
  /// requires dimensions of input image and output image (usually the
  /// same) You must supply the dimensions of the CAHVOR image that
  /// you are dewarping, as well as the dimensions of the dewarped
  /// cahv image (if they differ).
  CAHVModel linearize_camera(CAHVORModel &camera_model, 
                             unsigned cahvor_image_width, 
                             unsigned cahvor_image_height,
                             unsigned cahv_image_width,
                             unsigned cahv_image_height);
  
}}	// namespace vw::camera

#endif	//__CAMERAMODEL_CAHVOR_H__

