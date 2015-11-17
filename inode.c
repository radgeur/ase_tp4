#include "inode.h"

/*Read the inode*/
void read_inode(unsigned int inumber, struct inode_s inode){
    read_nbloc(inumber,inode,sizeof(struct inode_s));
}

/*Write on the inode*/
void write_inode(unsigned int inumber, struct inode_s inode){
    write_nbloc(inumber, inode, sizeof(struct inode_s));
}


/*Create a new inode initialized with 0*/
unsigned int create_inode(enum file_type_e type){
    
    /*Create the inode initialized with 0*/
    struct inode_s inode;
    int i;
    inode.type = type;
    inode.size = 0;
    for(i=0;i<NDIRECT,i++){
	inode.direct[i] = 0;
    }
    inode.indirect = 0;
    inode.two_indirect = 0;

    /*Place the inode on a free bloc*/
    inumber = new_bloc();
    if(inumber = 0){
	return 0;
    }
    write_inode(inumber, &inode);
    return inumber;
}

/*Delete a inode in the memory*/
int delete_inode(unsigned int inumber){

    /*Free the direct blocs*/
    int i;
    read_inode(inumber,&inode);
    free_blocs(inode.direct,NDIRECT);

    /*Free the indirect blocs if it s exists*/
    if(inode.indirect){
	unsigned bloc[NBPB];
	read_nbloc(inode.indirect, bloc, NBPB*sizeof(unsigned));
	free_blocs(bloc,NBPB);
	free_bloc(inode.indirect);
    }

    /*Free the double indirect blocs if it s exists*/
    if(inode.two_indirect){
	unsigned bbloc[NBPB];
	read_nbloc(inode.two_indirect,bbloc,NBPB*sizeof(unsigned));
	for(i=0; i<NBPB; i++){
	    if(bbloc[i]){
		unsigned bbbloc[NBPB];
		read_nbloc(inode.bbloc[i], bbbloc, NBPB*sizeof(unsigned));
		free_blocs(bbbloc,NBPB);
		free_bloc(bbloc[i]);
	    }
	}
	free_bloc(inode.two_indirect);
    }

    /*Free the bloc with the inode */
    free_bloc(inumber);
}

/*Return the number of bloc ont the volume which is the FBloc of the inode*/
/*If the bloc isn t allocated, the function allocated it if do allocate is true*/
unsigned int vbloc_of_fbloc(unsigned int inumber, unsigned int Fbloc, bool_t do_allocate){
    unsigned bloc[NBPB];
    unsigned bbloc[NBPB];
    read_inode(inumber,&inode);
    if(Fbloc<NDIRECT){
	if(do_allocate){
	    if(inode.direct[Fbloc]==0){
		inode.direct[Fbloc] = new_bloc_zero();
		write_inode(inumber, &inode);
	    }
	}
	return inode.direct[Fbloc];
    }
    Fbloc -=NDIRECT;
    if(Fbloc < NBPB){
	if(inode.indirect == 0){
	    return 0;
	}
	if(do_allocate){
	    inode.indirect = new_bloc_zero();
	    write_inode(inumber, &inode);
	}
	read_nbloc(inode.indirect, bloc, NBPB*sizeof(unsigned));
	if(do_allocate){
	    if(bloc[Fbloc] == 0){
		bloc[Fbloc] = new_bloc_zero();
		write_nbloc(inode.indirect,bloc, NBPB*sizeof(unsigned));
	    }
	}
	return bloc[Fbloc];
    }
    Fbloc -=NBPB;
    if(Fbloc <NBPB*NBPB){
	if(inode.two_indirect == 0){
	    return 0;
	}
	if(do_allocate){
	    inode.two_indirect = new_bloc_zero();
	    write_inode(inumber, &inode);
	}
	read_nbloc(inode.two_indirect,bloc, NBPB*sizeof(unsigned));
	if(do_allocate){
	    if(bloc[Fbloc] == 0){
		bloc[Fbloc] = new_bloc_zero();
		write_nbloc(bloc[Fbloc],bloc, NBPB*sizeof(unsigned));
	    }
	}
	n = Fbloc/NBPB;
	if(bloc[n] == 0){
	    return 0;
	}
	if(do_allocate){
	    bloc[n] = new_bloc_zero();
	    write_nbloc(bloc[n],bloc, NBPB*sizeof(unsigned));
	}
	read_nbloc(bloc[n], bbloc, NBPB*sizeof(unsigned));
	if(do_allocate){
	    if(bbloc[Fbloc] == 0){
		bbloc[Fbloc] = new_bloc_zero();
		write_nbloc(bbloc[Fbloc],bbloc, NBPB*sizeof(unsigned));
	    }
	}
	nn=Fbloc%NBPB;
	return Fbloc[nn];
    }
    return -42;
}
