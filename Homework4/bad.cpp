
void removeBad(list<Movie*>& li)
{
    //  call in iterator
    list<Movie*>::iterator it;
    // set to begin
    it = li.begin();
    while( it != li.end())
    {
        // notice iterator
        // is a pointer to a movie pointer
        // thus ..
        int rate = (*it)->rating();
        if( rate < 55 )
        {
            delete *it;
            it = li.erase(it);
        }else
            it++;
    }
}

