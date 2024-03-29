# Type-Builder for Oberon

```
@Def(file: builder.h)
	#pragma once
	@put(includes);
	@put(globals);
	class Builder {
		private:
			@put(privates);
		public:
			@put(publics);
	};
	#if builder_IMPL
		@put(impl);
	#endif
@End(file: builder.h)
```

```
@Def(file: builder.cpp)
	#define builder_IMPL 1
	#include "builder.h"
@End(file: builder.cpp)
```

```
@def(publics)
	void open_scope();
	void close_scope();
@end(publics)
```

```
@def(impl)
	void Builder::open_scope() {
		@put(open scope);
	}
@end(impl)
```

```
@add(impl)
	void Builder::close_scope() {
		@put(close scope);
	}
@end(impl)
```

```
@def(globals)
	enum class Obj_Class {
		c_head = 0, c_const = 1,
		c_var = 2, c_par = 3, c_fld = 4,
		c_typ = 5, c_sproc = 6,
		c_sfunc = 7, c_mod = 8
	};
@end(globals)
```

```
@def(includes)
	#include <string>
@end(includes)
```

```
@add(globals)
	class Object {
		private:
			Obj_Class _class;
			bool _exported { false };
			bool _readonly { false };
			Object *_next = nullptr;
			Object *_descendants = nullptr;
			std::string _name;
		public:
			Object(Obj_Class c, Object *d):
				_class { c },
				_descendants { d }
			{ }

			Object *descendants() {
				return _descendants;
			}

			~Object() {
				if (_descendants) {
					delete _descendants;
					_descendants = nullptr;
				}
			}
	};
@end(globals)
```

```
@def(privates)
	Object *_top_scope { nullptr };
@end(privates)
```

```
@add(publics)
	~Builder() {
		if (_top_scope) {
			delete _top_scope;
			_top_scope = nullptr;
		}
	}
@end(publics)
```

```
@add(open scope)
	auto o { new Object { Obj_Class::c_head, _top_scope }};
	_top_scope = o;
@end(open scope)
```

```
@add(close scope)
	auto o { _top_scope };
	if (o) {
		_top_scope = o->descendants();
		delete o;
	}
@end(close scope)
```

