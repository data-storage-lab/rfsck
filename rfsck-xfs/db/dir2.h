/*
 * Copyright (c) 2000-2001,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write the Free Software Foundation,
 * Inc.,  51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/*
 * common types across directory formats
 */
extern const field_t	dir2_block_tail_flds[];
extern const field_t	dir2_data_free_flds[];
extern const field_t	dir2_data_union_flds[];
extern const field_t	dir2_leaf_tail_flds[];
extern const field_t	dir2_leaf_entry_flds[];

extern const field_t	da_node_entry_flds[];

/*
 * dirv2 specific types
 */
extern const field_t	dir2_flds[];
extern const field_t	dir2_hfld[];
extern const field_t	dir2_data_hdr_flds[];
extern const field_t	dir2_free_hdr_flds[];
extern const field_t	dir2_leaf_hdr_flds[];

extern const field_t	da_blkinfo_flds[];
extern const field_t	da_node_hdr_flds[];

/*
 * dirv3 specific types
 */
extern const field_t	dir3_flds[];
extern const field_t	dir3_hfld[];
extern const field_t	dir3_blkhdr_flds[];
extern const field_t	dir3_data_hdr_flds[];
extern const field_t	dir3_free_hdr_flds[];
extern const field_t	dir3_leaf_hdr_flds[];
extern const field_t	dir3_data_union_flds[];

extern const field_t	da3_blkinfo_flds[];
extern const field_t	da3_node_hdr_flds[];

static inline uint8_t *xfs_dir2_sf_inumberp(xfs_dir2_sf_entry_t *sfep)
{
	return &(sfep)->name[(sfep)->namelen];
}

extern int	dir2_data_union_size(void *obj, int startoff, int idx);
extern int	dir2_size(void *obj, int startoff, int idx);

extern const struct xfs_buf_ops xfs_dir3_db_buf_ops;
