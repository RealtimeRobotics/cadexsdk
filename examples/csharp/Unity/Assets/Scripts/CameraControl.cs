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


using UnityEngine;

public class CameraControl : MonoBehaviour
{
    Transform myTarget;
    Camera myCameraComponent;
    public float MovementSpeed = 1f;

    private void Start()
    {
        myCameraComponent = GetComponent<Camera>();
    }

    public void SetTarget(Transform theTarget)
    {
        myTarget = theTarget;
        FitTarget();
    }

    void FitTarget() 
    {
        if (!myTarget) 
        {
            return;
        }

        // Getting target gameObject bounds
        MeshRenderer[] aMeshRenderers = myTarget.GetComponentsInChildren<MeshRenderer>();
        if (aMeshRenderers.Length == 0) 
        {
            return;
        }
        Bounds aBounds = aMeshRenderers[0].bounds;
        foreach (MeshRenderer aRenderer in aMeshRenderers) 
        {
            Vector3 min = aBounds.min;
            min.x = Mathf.Min(min.x, aRenderer.bounds.min.x);
            min.y = Mathf.Min(min.y, aRenderer.bounds.min.y);
            min.z = Mathf.Min(min.z, aRenderer.bounds.min.z);
            Vector3 max = aBounds.max;
            max.x = Mathf.Max(max.x, aRenderer.bounds.max.x);
            max.y = Mathf.Max(max.y, aRenderer.bounds.max.y);
            max.z = Mathf.Max(max.z, aRenderer.bounds.max.z);
            aBounds.SetMinMax(min, max);
        }

        // Moving camera to fit bounds in FOV
        // Base idea - https://forum.unity.com/threads/fit-object-exactly-into-perspective-cameras-field-of-view-focus-the-object.496472/
        float aCameraDistance = 1.0f; // Distance scale factor
        float anObjectSize = aBounds.size.magnitude;
        float aCameraView = 2.0f * Mathf.Tan(0.5f * Mathf.Deg2Rad * myCameraComponent.fieldOfView); // Visible height 1 unit in front
        float aDistance = aCameraDistance * anObjectSize / aCameraView; // Combined wanted distance from the object
        aDistance += 0.5f * anObjectSize; // Estimated offset from the center to the outside of the object
        myCameraComponent.transform.position = aBounds.center - aDistance * myCameraComponent.transform.forward;
    }

    void Update()
    {
        float aDistance = myTarget?(myTarget.position - gameObject.transform.position).magnitude : 100;
        aDistance = aDistance < 100 ? 100 : aDistance;
        myCameraComponent.farClipPlane = aDistance > 1200 ? aDistance+800 : 2000;
        float x = Input.GetAxis("Horizontal") * Time.deltaTime * aDistance * MovementSpeed;
        float y = 0.0f;
        float z = Input.GetAxis("Vertical") * Time.deltaTime * aDistance * MovementSpeed;

        if (Input.GetMouseButton(1))
        {
            float rx = Input.GetAxis("Mouse Y") * 2.0f;
            float ry = Input.GetAxis("Mouse X") * 2.0f;

            Vector3 rot = transform.eulerAngles;
            rot.x -= rx;
            rot.y += ry;
            transform.eulerAngles = rot;
        }
        if (Input.GetMouseButton(2))
        {
            x -= Input.GetAxis("Mouse X") * Time.deltaTime * aDistance * MovementSpeed;
            y -= Input.GetAxis("Mouse Y") * Time.deltaTime * aDistance * MovementSpeed;
        }
        z += Input.GetAxis("Mouse ScrollWheel")* aDistance*0.1f;

        transform.Translate(x, y, z);

        if (Input.GetKeyDown(KeyCode.F)) 
        {
            FitTarget();
        }
    }
}