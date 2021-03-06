
#ifndef ARTCFD_SHAPEFUNCTIONFACTORY_HPP
#define ARTCFD_SHAPEFUNCTIONFACTORY_HPP

// Std Lib Include Zone
#include <unordered_map>

// ArtPDE Lib Include Zone

#include "ShapeFunction.h"

namespace art_pde{

	enum class ElementType2D{ Q4, Q8, Q9, T3 };
	enum class ElementType3D{ Hexa8 };

	template<class ShapeFunctionType, class Identifier = Nulltype>
	class ShapeFunctionFactory{
	public:
		using THIS = ShapeFunctionFactory< ShapeFunctionType, Identifier>;
		friend class SingletonHolder<THIS>;
		ShapeFunctionType& getInstance(){
			return SingletonHolder<ShapeFunctionType>::instance();
		}
	private:
		ShapeFunctionFactory(){};
		ShapeFunctionFactory(const ShapeFunctionFactory&){};
		ShapeFunctionFactory& operator=(const ShapeFunctionFactory&){};
	};


	template<>
	class ShapeFunctionFactory<
		ShapeFunction< TypeList3(Dim2D, ElementType, LagrangePoly) >, ElementType2D>
	{
	public:
		using THIS = ShapeFunctionFactory<
			ShapeFunction< TypeList3(Dim2D, ElementType, LagrangePoly) >, ElementType2D>;
		using ReturnFunc = ShapeFunction< TypeList3(Dim2D, ElementType, LagrangePoly) >;
		friend class SingletonHolder<THIS>;
		ReturnFunc& getInstance(ElementType2D& key){
			return table.at(key);
		}
	private:
		std::unordered_map<ElementType2D, ReturnFunc&> table;
		ShapeFunctionFactory(){
			table.insert({ ElementType2D::Q4, SingletonHolder<ShapeFunction< TypeList3(Dim2D, Q4, LagrangePoly) > >::instance() });
			table.insert({ ElementType2D::T3, SingletonHolder<ShapeFunction< TypeList3(Dim2D, T3, LagrangePoly) > >::instance() });
			table.insert({ ElementType2D::Q8, SingletonHolder<ShapeFunction< TypeList3(Dim2D, Q8, LagrangePoly) > >::instance() });
			table.insert({ ElementType2D::Q9, SingletonHolder<ShapeFunction< TypeList3(Dim2D, Q9, LagrangePoly) > >::instance() });
			// ...
		}
		ShapeFunctionFactory(const ShapeFunctionFactory&){};
		ShapeFunctionFactory& operator=(const ShapeFunctionFactory&){};

	};

	template<>
	class ShapeFunctionFactory<
		ShapeFunction< TypeList3(Dim3D, ElementType, LagrangePoly) >, ElementType3D>
	{
	public:
		using THIS = ShapeFunctionFactory<
			ShapeFunction< TypeList3(Dim3D, ElementType, LagrangePoly) >, ElementType3D>;
		using ReturnFunc = ShapeFunction< TypeList3(Dim3D, ElementType, LagrangePoly) >;
		friend class SingletonHolder<THIS>;
		ReturnFunc& getInstance(ElementType3D& key){
			return table.at(key);
		}
	private:
		std::unordered_map<ElementType3D, ReturnFunc&> table;
		ShapeFunctionFactory(){
			table.insert({ ElementType3D::Hexa8, SingletonHolder<ShapeFunction< TypeList3(Dim3D, Hexa8, LagrangePoly) > >::instance() });
			// ...
		}
		ShapeFunctionFactory(const ShapeFunctionFactory&){};
		ShapeFunctionFactory& operator=(const ShapeFunctionFactory&){};

	};

}

#endif 



//using namespace art_pde;
//
//template<typename T>
//void disp(std::vector<T> a){
//	for (auto i : a){
//		std::cout << i << "\n";
//	}
//}
//
//template<typename T>
//void disp(std::vector<std::vector<T>> a){
//	for (int i = 0; i < a.size(); ++i){
//		for (int j = 0; j < a[i].size(); ++j){
//			std::cout << a[i][j] << " ";
//		}
//		std::cout << "\n";
//	}
//}
//
//int main() {
//
//
//
//	auto& fem_shape = SingletonHolder < ShapeFunctionFactory <
//		ShapeFunction< TypeList3(Dim2D, ElementType, LagrangePoly) >,
//		ElementType2D >> ::instance();
//
//	std::vector<ElementType2D> table{ ElementType2D::Q4, ElementType2D::Q8, ElementType2D::T3, ElementType2D::Q9 };
//	std::vector<std::string> name{ "Q4", "Q8", "T3", "Q9" };
//	for (int i = 0; i < table.size(); ++i){
//		auto& func = fem_shape.getInstance(table[i]);
//		std::cout << "=====" << name[i] << " N value" << "=====" << "\n";
//		disp(func.evaluate_shape(Point<Dim2D, IsoparametricCoordinate>(1.0, 1.0)));
//
//		std::cout << "=====" << name[i] << " Nx value" << "=====" << "\n";
//		disp(func.evaluate_grad(Point<Dim2D, IsoparametricCoordinate>(1.0, 1.0)));
//	}
//
//
//	auto& meshless_shape = SingletonHolder < ShapeFunctionFactory <
//		ShapeFunction< TypeList3(Dim2D, ScatterPoint, Multiquadric) >,
//		Nulltype >> ::instance();
//
//	auto& func = meshless_shape.getInstance();
//
//
//
//
//	system("pause");
//	return 0;
//}