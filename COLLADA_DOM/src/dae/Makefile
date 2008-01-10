#!/usr/bin/make
# Copyright 2006 Sony Computer Entertainment Inc.
#
# Licensed under the SCEA Shared Source License, Version 1.0 (the "License"); you may not use this 
# file except in compliance with the License. You may obtain a copy of the License at:
# http://research.scea.com/scea_shared_source_license.html
#
# Unless required by applicable law or agreed to in writing, software distributed under the License 
# is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
# implied. See the License for the specific language governing permissions and limitations under the 
# License. 

# target file(s)
ROOT_DIR :=	../..
LIBRARY := dom
OUTPUT_DIR := $(ROOT_DIR)/lib

# definitions
include $(ROOT_DIR)/build/makedefs.txt

# files
SRC	:= dae.cpp \
       daeArray.cpp \
       daeAtomicType.cpp \
       daeDatabase.cpp \
       daeDocument.cpp \
       daeDom.cpp \
       daeElement.cpp \
       daeError.cpp \
       daeErrorHandler.cpp \
       daeIDRef.cpp \
       daeMemorySystem.cpp \
       daeMetaAny.cpp \
       daeMetaAttribute.cpp \
       daeMetaChoice.cpp \
       daeMetaCMPolicy.cpp \
       daeMetaElement.cpp \
       daeMetaElementAttribute.cpp \
       daeMetaGroup.cpp \
       daeMetaSequence.cpp \
       daeRawResolver.cpp \
       daeSIDResolver.cpp \
       daeStringRef.cpp \
       daeStringTable.cpp \
       daeURI.cpp \
       domAny.cpp \
       daeStandardURIResolver.cpp \
       daeIOPluginCommon.cpp \
       daeRefCountedObj.cpp \
       ../modules/stdErrPlugin/stdErrPlugin.cpp \
       ../modules/STLDatabase/daeSTLDatabase.cpp \
       ../modules/LIBXMLPlugin/daeLIBXMLPlugin.cpp \
       daeTinyXMLPlugin.cpp

ifeq ($(COLLADA_VERSION), 1.4)
# Add the 1.4 source files
SRC	+= ../1.4/dom/domAccessor.cpp \
       ../1.4/dom/domAnimation.cpp \
       ../1.4/dom/domAnimation_clip.cpp \
       ../1.4/dom/domAsset.cpp \
       ../1.4/dom/domBind_material.cpp \
       ../1.4/dom/domBool_array.cpp \
       ../1.4/dom/domBox.cpp \
       ../1.4/dom/domCamera.cpp \
       ../1.4/dom/domCapsule.cpp \
       ../1.4/dom/domCg_connect_param.cpp \
       ../1.4/dom/domCg_newarray_type.cpp \
       ../1.4/dom/domCg_newparam.cpp \
       ../1.4/dom/domCg_param_type.cpp \
       ../1.4/dom/domCg_sampler1D.cpp \
       ../1.4/dom/domCg_sampler2D.cpp \
       ../1.4/dom/domCg_sampler3D.cpp \
       ../1.4/dom/domCg_samplerCUBE.cpp \
       ../1.4/dom/domCg_samplerDEPTH.cpp \
       ../1.4/dom/domCg_samplerRECT.cpp \
       ../1.4/dom/domCg_setarray_type.cpp \
       ../1.4/dom/domCg_setparam.cpp \
       ../1.4/dom/domCg_setparam_simple.cpp \
       ../1.4/dom/domCg_setuser_type.cpp \
       ../1.4/dom/domCg_surface_type.cpp \
       ../1.4/dom/domChannel.cpp \
       ../1.4/dom/domCOLLADA.cpp \
       ../1.4/dom/domCommon_color_or_texture_type.cpp \
       ../1.4/dom/domCommon_float_or_param_type.cpp \
       ../1.4/dom/domCommon_newparam_type.cpp \
       ../1.4/dom/domCommon_transparent_type.cpp \
       ../1.4/dom/domConstants.cpp \
       ../1.4/dom/domController.cpp \
       ../1.4/dom/domConvex_mesh.cpp \
       ../1.4/dom/domCylinder.cpp \
       ../1.4/dom/domEffect.cpp \
       ../1.4/dom/domEllipsoid.cpp \
       ../1.4/dom/domExtra.cpp \
       ../1.4/dom/domFloat_array.cpp \
       ../1.4/dom/domForce_field.cpp \
       ../1.4/dom/domFx_annotate_common.cpp \
       ../1.4/dom/domFx_annotate_type_common.cpp \
       ../1.4/dom/domFx_basic_type_common.cpp \
       ../1.4/dom/domFx_clearcolor_common.cpp \
       ../1.4/dom/domFx_cleardepth_common.cpp \
       ../1.4/dom/domFx_clearstencil_common.cpp \
       ../1.4/dom/domFx_code_profile.cpp \
       ../1.4/dom/domFx_colortarget_common.cpp \
       ../1.4/dom/domFx_depthtarget_common.cpp \
       ../1.4/dom/domFx_include_common.cpp \
       ../1.4/dom/domFx_newparam_common.cpp \
       ../1.4/dom/domFx_profile_abstract.cpp \
       ../1.4/dom/domFx_sampler1D_common.cpp \
       ../1.4/dom/domFx_sampler2D_common.cpp \
       ../1.4/dom/domFx_sampler3D_common.cpp \
       ../1.4/dom/domFx_samplerCUBE_common.cpp \
       ../1.4/dom/domFx_samplerDEPTH_common.cpp \
       ../1.4/dom/domFx_samplerRECT_common.cpp \
       ../1.4/dom/domFx_stenciltarget_common.cpp \
       ../1.4/dom/domFx_surface_common.cpp \
       ../1.4/dom/domFx_surface_format_hint_common.cpp \
       ../1.4/dom/domFx_surface_init_common.cpp \
       ../1.4/dom/domFx_surface_init_cube_common.cpp \
       ../1.4/dom/domFx_surface_init_from_common.cpp \
       ../1.4/dom/domFx_surface_init_planar_common.cpp \
       ../1.4/dom/domFx_surface_init_volume_common.cpp \
       ../1.4/dom/domGeometry.cpp \
       ../1.4/dom/domGles_basic_type_common.cpp \
       ../1.4/dom/domGles_newparam.cpp \
       ../1.4/dom/domGles_pipeline_settings.cpp \
       ../1.4/dom/domGles_sampler_state.cpp \
       ../1.4/dom/domGles_texcombiner_argumentAlpha_type.cpp \
       ../1.4/dom/domGles_texcombiner_argumentRGB_type.cpp \
       ../1.4/dom/domGles_texcombiner_commandAlpha_type.cpp \
       ../1.4/dom/domGles_texcombiner_commandRGB_type.cpp \
       ../1.4/dom/domGles_texcombiner_command_type.cpp \
       ../1.4/dom/domGles_texenv_command_type.cpp \
       ../1.4/dom/domGles_texture_constant_type.cpp \
       ../1.4/dom/domGles_texture_pipeline.cpp \
       ../1.4/dom/domGles_texture_unit.cpp \
       ../1.4/dom/domGlsl_newarray_type.cpp \
       ../1.4/dom/domGlsl_newparam.cpp \
       ../1.4/dom/domGlsl_param_type.cpp \
       ../1.4/dom/domGlsl_setarray_type.cpp \
       ../1.4/dom/domGlsl_setparam.cpp \
       ../1.4/dom/domGlsl_setparam_simple.cpp \
       ../1.4/dom/domGlsl_surface_type.cpp \
       ../1.4/dom/domGl_hook_abstract.cpp \
       ../1.4/dom/domGl_pipeline_settings.cpp \
       ../1.4/dom/domGl_sampler1D.cpp \
       ../1.4/dom/domGl_sampler2D.cpp \
       ../1.4/dom/domGl_sampler3D.cpp \
       ../1.4/dom/domGl_samplerCUBE.cpp \
       ../1.4/dom/domGl_samplerDEPTH.cpp \
       ../1.4/dom/domGl_samplerRECT.cpp \
       ../1.4/dom/domIDREF_array.cpp \
       ../1.4/dom/domImage.cpp \
       ../1.4/dom/domInputGlobal.cpp \
       ../1.4/dom/domInputLocal.cpp \
       ../1.4/dom/domInputLocalOffset.cpp \
       ../1.4/dom/domInstanceWithExtra.cpp \
       ../1.4/dom/domInstance_camera.cpp \
       ../1.4/dom/domInstance_controller.cpp \
       ../1.4/dom/domInstance_effect.cpp \
       ../1.4/dom/domInstance_force_field.cpp \
       ../1.4/dom/domInstance_geometry.cpp \
       ../1.4/dom/domInstance_light.cpp \
       ../1.4/dom/domInstance_material.cpp \
       ../1.4/dom/domInstance_node.cpp \
       ../1.4/dom/domInstance_physics_material.cpp \
       ../1.4/dom/domInstance_physics_model.cpp \
       ../1.4/dom/domInstance_rigid_body.cpp \
       ../1.4/dom/domInstance_rigid_constraint.cpp \
       ../1.4/dom/domInt_array.cpp \
       ../1.4/dom/domLibrary_animations.cpp \
       ../1.4/dom/domLibrary_animation_clips.cpp \
       ../1.4/dom/domLibrary_cameras.cpp \
       ../1.4/dom/domLibrary_controllers.cpp \
       ../1.4/dom/domLibrary_effects.cpp \
       ../1.4/dom/domLibrary_force_fields.cpp \
       ../1.4/dom/domLibrary_geometries.cpp \
       ../1.4/dom/domLibrary_images.cpp \
       ../1.4/dom/domLibrary_lights.cpp \
       ../1.4/dom/domLibrary_materials.cpp \
       ../1.4/dom/domLibrary_nodes.cpp \
       ../1.4/dom/domLibrary_physics_materials.cpp \
       ../1.4/dom/domLibrary_physics_models.cpp \
       ../1.4/dom/domLibrary_physics_scenes.cpp \
       ../1.4/dom/domLibrary_visual_scenes.cpp \
       ../1.4/dom/domLight.cpp \
       ../1.4/dom/domLines.cpp \
       ../1.4/dom/domLinestrips.cpp \
       ../1.4/dom/domLookat.cpp \
       ../1.4/dom/domMaterial.cpp \
       ../1.4/dom/domMatrix.cpp \
       ../1.4/dom/domMesh.cpp \
       ../1.4/dom/domMorph.cpp \
       ../1.4/dom/domName_array.cpp \
       ../1.4/dom/domNode.cpp \
       ../1.4/dom/domP.cpp \
       ../1.4/dom/domParam.cpp \
       ../1.4/dom/domPhysics_material.cpp \
       ../1.4/dom/domPhysics_model.cpp \
       ../1.4/dom/domPhysics_scene.cpp \
       ../1.4/dom/domPlane.cpp \
       ../1.4/dom/domPolygons.cpp \
       ../1.4/dom/domPolylist.cpp \
       ../1.4/dom/domProfile_CG.cpp \
       ../1.4/dom/domProfile_COMMON.cpp \
       ../1.4/dom/domProfile_GLES.cpp \
       ../1.4/dom/domProfile_GLSL.cpp \
       ../1.4/dom/domRigid_body.cpp \
       ../1.4/dom/domRigid_constraint.cpp \
       ../1.4/dom/domRotate.cpp \
       ../1.4/dom/domSampler.cpp \
       ../1.4/dom/domScale.cpp \
       ../1.4/dom/domSkew.cpp \
       ../1.4/dom/domSkin.cpp \
       ../1.4/dom/domSource.cpp \
       ../1.4/dom/domSphere.cpp \
       ../1.4/dom/domSpline.cpp \
       ../1.4/dom/domTapered_capsule.cpp \
       ../1.4/dom/domTapered_cylinder.cpp \
       ../1.4/dom/domTargetableFloat.cpp \
       ../1.4/dom/domTargetableFloat3.cpp \
       ../1.4/dom/domTechnique.cpp \
       ../1.4/dom/domTranslate.cpp \
       ../1.4/dom/domTriangles.cpp \
       ../1.4/dom/domTrifans.cpp \
       ../1.4/dom/domTristrips.cpp \
       ../1.4/dom/domTypes.cpp \
       ../1.4/dom/domVertices.cpp \
       ../1.4/dom/domVisual_scene.cpp 
endif

INCLUDE_DIR += $(ROOT_DIR)/include
INCLUDE_DIR += $(ROOT_DIR)/include/$(COLLADA_VERSION)/

# Do we want libxml, TinyXML, or both?
ifneq ($(PLATFORM_NAME), ps3)
# On Linux, enable libxml and disable TinyXml by default
LIBXML := 1
TINYXML := 0
else
# On PS3, disable libxml and enable TinyXml by default
LIBXML := 0
TINYXML := 1
endif

ifneq ($(LIBXML), 0)
CCOPT += -D"DOM_INCLUDE_LIBXML"
INCLUDE_DIR += /usr/include/libxml2
LIBRARIES += -lxml2
endif
ifeq ($(TINYXML), 1)
CCOPT += -D"DOM_INCLUDE_TINYXML"
INCLUDE_DIR += $(ROOT_DIR)/../external-libs/tinyxml/
LIBRARIES += $(ROOT_DIR)/../external-libs/tinyxml/lib/$(PLATFORM_NAME)/libtinyxml.a
endif

ifeq ($(PLATFORM_NAME), ps3)
# On PS3, we need to be told where to find pcre
INCLUDE_DIR += $(ROOT_DIR)/../external-libs/pcre
LCOPT += -L$(ROOT_DIR)/../external-libs/pcre/lib/$(PLATFORM_NAME)

# We have no getcwd on PS3
CCOPT += -DNO_GETCWD
endif

LIBRARIES += -lpcre -lpcrecpp

# rules
include          $(ROOT_DIR)/build/makerules.txt
