/// executing order is important
/// We usually place metafuncs calling statements in
/// struct or class to ensure statements are in order
template <typename T> struct RemoveReferenceConst_ {
private:
  using inter_type = typename std::remove_reference<T>::type;

public:
  using type = typename std::remove_const<inter_type>::type;
};
template <typename T>
using RemoveReferenceConst = typename RemoveReferenceConst_<T>::type;

RemoveReferenceConst<const int &> h = 3;