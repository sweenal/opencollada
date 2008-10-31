#ifndef __COLLADA_INSTANCE_GEOMETRY_UTIL_H__
#define __COLLADA_INSTANCE_GEOMETRY_UTIL_H__

#include "HelperPrerequisites.h"

namespace COLLADADomHelper {
    /// A mapping between material symbol and a domMaterial pointer.
    typedef std::map<std::string, domMaterial*> SymbolMaterialMap;
    /// A mapping between a domMaterial pointer and multiple material symbols.
    typedef std::multimap<domMaterial*, std::string> MaterialSymbolMap;

    class InstanceGeometryUtil
    {
    public:                
        /** @todo getSymbolMaterialMapping documentation	
        	@param instance
        	@param map
        	@return
        */
        static void getSymbolMaterialMapping(const domInstance_geometryRef& instance, SymbolMaterialMap& map);
		static void getSymbolMaterialMapping(const domInstance_geometry* instance, SymbolMaterialMap& map);
		static void getSymbolMaterialMapping(const domInstance_geometry& instance, SymbolMaterialMap& map);
    private:
        InstanceGeometryUtil();
    };
}

#endif //__COLLADA_INSTANCE_GEOMETRY_UTIL_H__
