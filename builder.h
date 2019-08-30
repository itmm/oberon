
#line 4 "builder.x"

	#pragma once
	
#line 62 "builder.x"

	#include <string>

#line 6 "builder.x"
;
	
#line 51 "builder.x"

	enum class Obj_Class {
		c_head = 0, c_const = 1,
		c_var = 2, c_par = 3, c_fld = 4,
		c_typ = 5, c_sproc = 6,
		c_sfunc = 7, c_mod = 8
	};

#line 68 "builder.x"

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

#line 7 "builder.x"
;
	class Builder {
		private:
			
#line 98 "builder.x"

	Object *_top_scope { nullptr };

#line 10 "builder.x"
;
		public:
			
#line 28 "builder.x"

	void open_scope();
	void close_scope();

#line 104 "builder.x"

	~Builder() {
		if (_top_scope) {
			delete _top_scope;
			_top_scope = nullptr;
		}
	}

#line 12 "builder.x"
;
	};
	#if builder_IMPL
		
#line 35 "builder.x"

	void Builder::open_scope() {
		
#line 115 "builder.x"

	auto o { new Object { Obj_Class::c_head, _top_scope }};
	_top_scope = o;

#line 37 "builder.x"
;
	}

#line 43 "builder.x"

	void Builder::close_scope() {
		
#line 122 "builder.x"

	auto o { _top_scope };
	if (o) {
		_top_scope = o->descendants();
		delete o;
	}

#line 45 "builder.x"
;
	}

#line 15 "builder.x"
;
	#endif
