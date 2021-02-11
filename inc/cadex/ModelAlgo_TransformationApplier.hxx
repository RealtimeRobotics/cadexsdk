// ****************************************************************************
// $Id$
//
// Copyright (C) 2008-2014, Roman Lygin. All rights reserved.
// Copyright (C) 2014-2020, CADEX. All rights reserved.
//
// This file is part of the CAD Exchanger software.
//
// This file may be used under the terms and conditions of the License
// Agreement supplied with the software.
//
// This file is provided "AS IS" WITH NO WARRANTY OF ANY KIND, EITHER EXPRESSED
// OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE WARRANTY OF DESIGN,
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// ****************************************************************************


#ifndef _ModelAlgo_TransformationApplier_HeaderFile
#define _ModelAlgo_TransformationApplier_HeaderFile

namespace cadex {

class ModelData_Transformation;
class ModelData_Shape;

class ModelAlgo_TransformationApplier
{
public:

    __CADEX_EXPORT static ModelData_Shape Transform (const ModelData_Shape& theShape,
                                                     const ModelData_Transformation& theTransformation);

};

}

#endif // _ModelAlgo_TransformationApplier_HeaderFile
