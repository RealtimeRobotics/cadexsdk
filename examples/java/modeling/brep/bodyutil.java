// ****************************************************************************
// $Id$
//
// Copyright (C) 2008-2014, Roman Lygin. All rights reserved.
// Copyright (C) 2014-2020, CADEX. All rights reserved.
//
// This file is part of the CAD Exchanger software.
//
// You may use this file under the terms of the BSD license as follows:
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// ****************************************************************************

import cadex.*;

public class bodyutil {
    public static ModelData_Body MakeSolidBody() {
        ModelData_Solid aSolid = ModelAlgo_TopoPrimitives.CreateBox(new ModelData_Point(-3., -3., -4.), new ModelData_Point(3., 3., -2.));
        ModelData_Body aBody = ModelData_Body.Create(aSolid);
        return aBody;
    }

    public static ModelData_Body MakeSheetBody() {
        ModelData_Plane aPlane = new ModelData_Plane(new ModelData_Point(0., 0., 0.), ModelData_Direction.ZDir());
        ModelData_Face aFace1 = new ModelData_Face(aPlane, -4., 0., -4., 0.);
        ModelData_Face aFace2 = new ModelData_Face(aPlane, 0., 4., 0., 4.);

        ModelData_Shell aShell = new ModelData_Shell(aFace1);
        aShell.Append(aFace2);

        ModelData_Body aBody = ModelData_Body.Create(aShell);
        return aBody;
    }

    public static ModelData_Body MakeWireframeBody() {
        ModelData_Axis2Placement anAxis = new ModelData_Axis2Placement();
        ModelData_Circle aCircle = new ModelData_Circle(anAxis, 5.);
        ModelData_Edge anEdge1 = new ModelData_Edge(aCircle, 1., 3.);
        ModelData_Edge anEdge2 = new ModelData_Edge(aCircle, 3., 6.);

        ModelData_Wire aWire = new ModelData_Wire(anEdge1);
        aWire.Append(anEdge2);

        ModelData_Body aBody = ModelData_Body.Create(aWire);
        return aBody;
    }

    public static ModelData_Body MakeAcornBody() {
        ModelData_Vertex aVertex = new ModelData_Vertex(new ModelData_Point(0., 0., 0.));
        ModelData_Body aBody = ModelData_Body.Create(aVertex);
        return aBody;
    }
}
