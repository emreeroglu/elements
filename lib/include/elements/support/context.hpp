/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(ELEMENTS_CONTEXT_APRIL_17_2016)
#define ELEMENTS_CONTEXT_APRIL_17_2016

#include <infra/string_view.hpp>
#include <artist/point.hpp>
#include <artist/rect.hpp>
#include <functional>

namespace cycfi::artist
{
   class canvas;
}

namespace cycfi::elements
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	// Contexts
	////////////////////////////////////////////////////////////////////////////////////////////////
   class view;
   class element;
   using artist::canvas;
   using artist::rect;

   struct basic_context
   {
      basic_context(elements::view& view_, elements::canvas& canvas_)
       : view(view_)
       , canvas(canvas_)
      {}

      basic_context(basic_context const&) = default;
      basic_context& operator=(basic_context const&) = delete;

      elements::view&        view;
      elements::canvas&      canvas;
   };

	////////////////////////////////////////////////////////////////////////////////////////////////
   // Forward declaration, access to view bounds
   rect view_bounds(elements::view const& v);

   ////////////////////////////////////////////////////////////////////////////////////////////////
   class context : public basic_context
   {
   public:

      context(context const& rhs, artist::rect bounds_)
       : basic_context(rhs.view, rhs.canvas), element(rhs.element)
       , parent(rhs.parent), bounds(bounds_), view_bounds(rhs.view_bounds)
      {}

      context(context const& parent_, element* element_, artist::rect bounds_)
       : basic_context(parent_.view, parent_.canvas), element(element_)
       , parent(&parent_), bounds(bounds_), view_bounds(parent_.view_bounds)
      {}

      context(class view& view_, class canvas& canvas_, element* element_, artist::rect bounds_)
       : basic_context(view_, canvas_), element(element_)
       , parent(nullptr), bounds(bounds_), view_bounds(elements::view_bounds(view_))
      {}

      context(context const&) = default;
      context& operator=(context const&) = delete;

      context sub_context() const
      {
         auto ctx = context{ *this };
         ctx.parent = this;
         return ctx;
      }

      template <typename T, typename F>
      void listen(F&& f)
      {
         _listener =
            [f](auto const& ctx, auto* e, auto what)
            {
               if (auto te = dynamic_cast<T*>(e))
                  f(ctx, *te, what);
            };
      }

      void notify(context const& ctx, string_view what, elements::element* e) const
      {
         if (_listener)
            _listener(ctx, e, what);
         if (parent)
            parent->notify(ctx, what, e);
      }

      elements::element*            element;
      context const*                parent;
      artist::rect                  bounds;
      artist::rect                	view_bounds;


   private:

      using listener_function =
         std::function<
            void(context const& ctx, elements::element*, string_view what)
         >;

      listener_function             _listener;
   };
}

#endif
