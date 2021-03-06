#ifndef _REVERSEGEOCODINGREQUEST_I
#define _REVERSEGEOCODINGREQUEST_I

#pragma SWIG nowarn=325

%module ReverseGeocodingRequest

#ifdef _CARTO_GEOCODING_SUPPORT

!proxy_imports(carto::ReverseGeocodingRequest, core.MapPos, core.Variant, projections.Projection)

%{
#include "geocoding/ReverseGeocodingRequest.h"
#include "components/Exceptions.h"
#include <memory>
%}

%include <std_shared_ptr.i>
%include <cartoswig.i>

%import "core/MapPos.i"
%import "core/Variant.i"
%import "projections/Projection.i"

!shared_ptr(carto::ReverseGeocodingRequest, geocoding.ReverseGeocodingRequest)

%attributeval(carto::ReverseGeocodingRequest, carto::MapPos, Location, getLocation)
%attribute(carto::ReverseGeocodingRequest, float, SearchRadius, getSearchRadius, setSearchRadius)
%attributestring(carto::ReverseGeocodingRequest, std::shared_ptr<carto::Projection>, Projection, getProjection)
%ignore carto::ReverseGeocodingRequest::getCustomParameters;
%std_exceptions(carto::ReverseGeocodingRequest::ReverseGeocodingRequest)
!standard_equals(carto::ReverseGeocodingRequest);
!custom_tostring(carto::ReverseGeocodingRequest);

%include "geocoding/ReverseGeocodingRequest.h"

#endif

#endif
