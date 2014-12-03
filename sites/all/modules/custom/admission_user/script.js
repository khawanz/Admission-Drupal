jQuery(document).ready(function(){
    jQuery('div').click(function() {
        var myclass = jQuery(this).attr('class');

        var click_element = myclass.substring(0,4);
        if(click_element === 'edit'){
            var end_class_name = myclass.substring(4,5);          
            jQuery('.cancel'+end_class_name).show();
            
            jQuery('.nilai_'+myclass).show();
            jQuery('.nilai_text_'+myclass).hide();

            jQuery('.is_lulus_'+myclass).show();
            jQuery('.is_lulus_text_'+myclass).hide();

            jQuery('.kategori_'+myclass).show();
            jQuery('.kategori_text_'+myclass).hide();

            jQuery('.prodi_'+myclass).show();
            jQuery('.prodi_text_'+myclass).hide();             

            jQuery('.submit-form-'+click_element).show();
            
            jQuery('.'+myclass).hide();
            
            
        }
        else if(click_element === 'canc'){
            var end_class_name = myclass.substring(6,7);
           
            jQuery('.nilai_edit'+end_class_name).hide();
            jQuery('.nilai_text_edit'+end_class_name).show();

            jQuery('.is_lulus_edit'+end_class_name).hide();
            jQuery('.is_lulus_text_edit'+end_class_name).show();

            jQuery('.kategori_edit'+end_class_name).hide();
            jQuery('.kategori_text_edit'+end_class_name).show();

            jQuery('.prodi_edit'+end_class_name).hide();
            jQuery('.prodi_text_edit'+end_class_name).show();             

            //jQuery('.submit-form-'+edit_class).show();
            
            jQuery('.cancel'+end_class_name).hide();
            jQuery('.edit'+end_class_name).show();
        }
       
//       jQuery('.'+myclass).data('clicked',true);
//       if(myclass.data('clicked')){alert('test');
//           jQuery('.submit-form').show();
//       }


             
      
   });
   
   //in registration form, set username = user email
   jQuery('#edit-mail').change(function(){
       var mail = jQuery('#edit-mail').val();
       jQuery('#edit-name').val(mail);
   });
});


