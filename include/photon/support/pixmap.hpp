/*=================================================================================================   Copyright (c) 2016 Joel de Guzman   Licensed under a Creative Commons Attribution-ShareAlike 4.0 International.   http://creativecommons.org/licenses/by-sa/4.0/=================================================================================================*/#if !defined(PHOTON_GUI_LIB_PIXMAP_SEPTEMBER_5_2016)#define PHOTON_GUI_LIB_PIXMAP_SEPTEMBER_5_2016#include <vector>#include <cairo.h>#include <photon/support/point.hpp>namespace photon{   class canvas;   ////////////////////////////////////////////////////////////////////////////////////////////////   // Pixmaps   ////////////////////////////////////////////////////////////////////////////////////////////////   class pixmap   {   public:      explicit          pixmap(char const* filename);                        pixmap(pixmap const& rhs) = delete;                        pixmap(pixmap&& rhs);                        ~pixmap();      pixmap&           operator=(pixmap const& rhs) = delete;      pixmap&           operator=(pixmap&& rhs);      photon::size      size() const;   private:      friend class canvas;      cairo_surface_t*  _surface;   };   using pixmap_ptr = std::shared_ptr<pixmap>;   ////////////////////////////////////////////////////////////////////////////////////////////////   // Inlines   ////////////////////////////////////////////////////////////////////////////////////////////////   inline pixmap::pixmap(pixmap&& rhs)    : _surface(rhs._surface)   {      rhs._surface = nullptr;   }   inline pixmap& pixmap::operator=(pixmap&& rhs)   {      _surface = rhs._surface;      rhs._surface = nullptr;      return *this;   }}#endif