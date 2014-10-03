template <typename T>
Rect<T>::Rect(T cx, T cy, T w, T h) : x(cx), y(cy), width(w), height(h) {

}

template <typename T>
template <typename U>
Rect<T>::Rect(const Rect<U>& rect) :
    x(static_cast<T>(rect.x)),
    y(static_cast<T>(rect.y)),
    width(static_cast<T>(rect.width)),
    height(static_cast<T>(rect.height))
{

}

template <typename T>
vec2<T> Rect<T>::getCenter() const {
    return vec2<T>(this->width / 2 + this->x, this->height / 2 + this->y);
}

template <typename T>
bool Rect<T>::isEmpty() const {
    SDL_Rect a;

    return SDL_RectEmpty(Copy(*this, &a)) == SDL_TRUE;
}

template <typename T>
bool Rect<T>::contains(T cx, T cy) const {
    SDL_Rect a;
    SDL_Point point(cx, cy);

    return SDL_PointInRect(&point, Copy(*this, &a));
}

template <typename T>
bool Rect<T>::contains(const vec2<T>& vec) const {
    SDL_Rect a;
    SDL_Point point;

    return SDL_PointInRect(Copy(vec, &point), Copy(*this, &a));
}

template <typename T>
bool Rect<T>::intersects(const Rect<T>& other, Rect<T>* intersection) const {
    SDL_Rect a, b;

    if (intersection != nullptr) {
        SDL_Rect c;

        const bool result = SDL_IntersectRect(Copy(*this, &a), Copy(other, &b), &c) == SDL_TRUE;
        Copy(&c, *intersection);

        return result;
    }

    return SDL_HasIntersection(Copy(*this, &a), Copy(*this, &b)) == SDL_TRUE;
}

template <typename T>
SDL_Rect* Copy(const Rect<T>& rect, SDL_Rect* dst) {
    if (dst) {
        dst->x = static_cast<int>(rect.x);
        dst->y = static_cast<int>(rect.y);
        dst->w = static_cast<int>(rect.width);
        dst->h = static_cast<int>(rect.height);
    }

    return dst;
}

template <typename T>
void Copy(const SDL_Rect* src, Rect<T>& rect) {
    if (src) {
        rect.x = static_cast<T>(src->x);
        rect.y = static_cast<T>(src->y);
        rect.width  = static_cast<T>(src->w);
        rect.height = static_cast<T>(src->h);
    }
}

template <typename T>
bool operator ==(const Rect<T>& lhs, const Rect<T>& rhs) {
    SDL_Rect a, b;

    return SDL_RectEquals(Copy(lhs, &a), Copy(rhs, &b));
}

template <typename T>
bool operator !=(const Rect<T>& lhs, const Rect<T>& rhs) {
    return !(lhs == rhs);
}
