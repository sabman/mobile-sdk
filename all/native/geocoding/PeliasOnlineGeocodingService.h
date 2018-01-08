/*
 * Copyright (c) 2016 CartoDB. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://cartodb.com/terms/
 */

#ifndef _CARTO_PELIASONLINEGEOCODINGSERVICE_H_
#define _CARTO_PELIASONLINEGEOCODINGSERVICE_H_

#if defined(_CARTO_GEOCODING_SUPPORT)

#include "geocoding/GeocodingService.h"

namespace carto {

    /**
     * An online geocoding service that uses Mapzen Pelias geocoder.
     * As the class connects to an external (non-CARTO) service, this class is provided "as-is",
     * future changes from the service provider may not be compatible with the implementation.
     * Note: this class is experimental and may change or even be removed in future SDK versions.
     */
    class PeliasOnlineGeocodingService : public GeocodingService {
    public:
        /**
         * Constructs a new instance of the PeliasOnlineGeocodingService given API key.
         * @param apiKey The API key to use (registered with Mapzen).
         */
        explicit PeliasOnlineGeocodingService(const std::string& apiKey);
        virtual ~PeliasOnlineGeocodingService();

        /**
         * Returns the autocomplete flag of the service.
         * @return The autocomplete flag of the service.
         */
        bool isAutocomplete() const;
        /**
         * Sets the autocomplete flag of the service.
         * By default this flag is off.
         * @param autocomplete The new value for autocomplete flag.
         */
        void setAutocomplete(bool autocomplete);

        /**
         * Returns the custom backend service URL.
         * @return The custom backend service URL. If this is not defined, an empty string is returned.
         */
        std::string getCustomServiceURL() const;
        /**
         * Sets the custom backend service URL. 
         * The custom URL should contain tag "{mode}" which will be set either to "autocomplete" or "search" based on the autocomplete state.
         * @param serviceURL The custom backend service URL to use. If this is empty, then the default service is used.
         */
        void setCustomServiceURL(const std::string& serviceURL);

        virtual std::vector<std::shared_ptr<GeocodingResult> > calculateAddresses(const std::shared_ptr<GeocodingRequest>& request) const;

    protected:
        static const std::string MAPZEN_SERVICE_URL;

        const std::string _apiKey;

        bool _autocomplete;

        std::string _serviceURL;

        mutable std::mutex _mutex;
    };
    
}

#endif

#endif
